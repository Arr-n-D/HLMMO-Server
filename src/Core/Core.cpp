#include "Core.h"

    Core::Core()
    {
    }

    Core::~Core()
    {
    }

    void Core::Initialize()
    {
        // this->InitializeSentry();

        // this->networkManager = NetworkManager::NetworkManager();
        this->networkManager.Initialize();
    }

    NetworkManager Core::GetNetworkManager()
    {
        return this->networkManager;
    }

    // void Core::InitializeSentry()
    // {
    //     sentry_options_t* options = sentry_options_new();
    //     sentry_options_set_dsn(options, "https://8b3930e3fd2d42bf80599879f3f2c93e@o4505591808196608.ingest.sentry.io/4505591809769472");
    //     // This is also the default-path. For further information and recommendations:
    //     // https://docs.sentry.io/platforms/native/configuration/options/#database-path
    //     sentry_options_set_database_path(options, ".sentry-native");
    //     sentry_options_set_release(options, "Hogwarts Legacy Together Server@0.1.0");
    //     //set environment to if we're in development or production
    // #if _DEBUG // #ifdef _DEBUG for Production/Development mode
    //     sentry_options_set_environment(options, "development");
    // #else
    //     sentry_options_set_environment(options, "production");
    // #endif

    //     sentry_options_set_handler_path(options, "crashpad_handler.exe");
    //     sentry_options_set_debug(options, 1);
    //     sentry_init(options);
    // }
