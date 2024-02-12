#pragma once
#include <thread>

namespace Utility {

	class Runable {
	private:
		std::thread thread;

	protected:
		virtual void run() = 0;

	public:
		Runable() {}
		virtual ~Runable() {}

		void start() {
			thread = std::thread(&Runable::run, this);
		}
	};
}

