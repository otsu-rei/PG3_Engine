#include "Thread.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/SxavengerSystem.h>

//* external
#include <imgui.h>

//* c++
#include <sstream>
#include <format>

////////////////////////////////////////////////////////////////////////////////////////////
// TaskThreadExecution class methods
////////////////////////////////////////////////////////////////////////////////////////////

void TaskThreadExecution::Execute(const Thread* const thread) {
	task_(thread);
}

void TaskThreadExecution::WaitCompleted() const {
	while (state_ != ExecutionState::kCompleted) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// Thread class methods
////////////////////////////////////////////////////////////////////////////////////////////

void Thread::Create(const std::function<void()>& threadFunc) {
	// threadに設定
	thread_ = std::thread(threadFunc);

	DirectXThreadContext::Init(1);
}

void Thread::Term() {
	isTerm_ = true;

	if (thread_.joinable()) {
		thread_.join();
	}

	DirectXThreadContext::ExecuteAllAllocators();
	Assert(task_ == nullptr, "tasks remain.");
}

void Thread::ExecuteTask() {
	if (task_ == nullptr) {
		return;
	}

	runtime_.Begin();
	isAvailable_ = false;
	//task_->SetState(ExecutionState::kRunning);

	task_->Execute(this);
	DirectXThreadContext::ExecuteAllAllocators();

	task_->SetState(ExecutionState::kCompleted);

	isAvailable_ = true;
	runtime_.End();

	task_ = nullptr;
}

void Thread::SystemDebugGui() {
	std::stringstream ss;
	ss << "[thread id]: " << thread_.get_id() << " ";
	ss << std::format("[available]: {}", isAvailable_) << " ";

	if (isAvailable_) {
		ImGui::Text(ss.str().c_str());

	} else {
		ImGui::TextDisabled(ss.str().c_str());

		if (ImGui::BeginItemTooltip()) {
			ImGui::SeparatorText("thread details");

			std::string text = "";
			text += std::format("[runtime]: {:.1f}sec", runtime_.GetElapsedTime<TimeUnit::s>().time) + "\n";
			text += std::format("[executing task]: {:p}", reinterpret_cast<void*>(task_.get())) + " ";

			ImGui::Text(text.c_str());

			ImGui::EndTooltip();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// ThreadCollection class methods
////////////////////////////////////////////////////////////////////////////////////////////

void ThreadCollection::Init(uint32_t threadCount) {

	// threadの設定
	threads_.resize(threadCount);

	for (auto& thread : threads_) {
		thread = std::make_unique<Thread>();

		thread->Create([&]() {
			ThreadLog("Begin Thread.");

			while (true) {
				{ //!< lock
					std::lock_guard<std::mutex> lock(mutex_);

					if (!tasks_.empty()) {
						thread->SetTask(GetTask());
					}
				}

				thread->ExecuteTask();

				if (thread->IsTerm()) {
					break;
				}
			}

			ThreadLog("End Thread.");
		});
	}
}

void ThreadCollection::Term() {
}

void ThreadCollection::SystemDebugGui() {
	ImGui::SeparatorText("thread collection");
	ImGui::Text(std::format("remain task queue size: {}", tasks_.size()).c_str());

	ImGui::SeparatorText("threads");
	for (auto& thread : threads_) {
		thread->SystemDebugGui();
	}
}

std::shared_ptr<TaskThreadExecution> ThreadCollection::GetTask() {
	auto task = tasks_.front();

	if (task->GetState() != ExecutionState::kWaiting) {
		tasks_.pop();
		return nullptr;
	}

	task->SetState(ExecutionState::kRunning);
	tasks_.pop();
	return task;
}
