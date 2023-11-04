/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "common.hpp"
#include "server.hpp"
#include "streaming.hpp"

#include "greeter/greeter.service.hpp"

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

int main(int argc, char** argv) 
{
    using namespace microservice;
    auto logger_instance = std::make_unique<logger>("GRPC Console");

    try
    {
        LOG(RAW_GREEN_TO_CONSOLE) << R"kek(
  _____                            _____                   _             
 / ____|                          |  __ \                 (_)            
| (___   ___ _ ____   _____ _ __  | |__) |   _ _ __  _ __  _ _ __   __ _ 
 \___ \ / _ \ '__\ \ / / _ \ '__| |  _  / | | | '_ \| '_ \| | '_ \ / _` |
 ____) |  __/ |   \ V /  __/ |    | | \ \ |_| | | | | | | | | | | | (_| |
|_____/ \___|_|    \_/ \___|_|    |_|  \_\__,_|_| |_|_| |_|_|_| |_|\__, |
                                                                    __/ |
                                                                   |___/ 
)kek";
        absl::ParseCommandLine(argc, argv);
        auto server_instance = std::make_unique<server>();
        server_instance->run(absl::GetFlag(FLAGS_port));

        server_instance.reset();
    }
    catch (const std::exception&)
    {

    }

    logger_instance.reset();

    return 0;
}