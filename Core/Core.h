#pragma once
#include "../sentry.h"
#include "../NetworkManager.h"

using namespace ArrND::NetworkManager;

namespace ArrND::Core {
	class Core {
		public:
			Core();
			~Core();
			void Initialize();


		private:
			void InitializeSentry();
			NetworkManager::NetworkManager networkManager;
	};
}
