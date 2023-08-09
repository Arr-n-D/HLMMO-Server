#pragma once
#include "../sentry.h"
#include "../NetworkManager.h"


	class Core {
		public:
			Core();
			~Core();
			void Initialize();


		private:
			void InitializeSentry();
			NetworkManager::NetworkManager networkManager;
	};
