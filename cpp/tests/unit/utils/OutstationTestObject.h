/*
 * Copyright 2013-2019 Automatak, LLC
 *
 * Licensed to Green Energy Corp (www.greenenergycorp.com) and Automatak
 * LLC (www.automatak.com) under one or more contributor license agreements.
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership. Green Energy Corp and Automatak LLC license
 * this file to you under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef OPENDNP3_UNITTESTS_OUTSTATION_TEST_OBJECT_H
#define OPENDNP3_UNITTESTS_OUTSTATION_TEST_OBJECT_H

#include <opendnp3/LogLevels.h>
#include <opendnp3/app/ITransactable.h>
#include <outstation/Database.h>
#include <outstation/OutstationContext.h>

#include "dnp3mocks/MockCommandHandler.h"
#include "dnp3mocks/MockLogHandler.h"
#include "dnp3mocks/MockLowerLayer.h"
#include "dnp3mocks/MockOutstationApplication.h"

#include <exe4cpp/MockExecutor.h>

#include <functional>

class OutstationTestObject
{

public:
    OutstationTestObject(const opendnp3::OutstationConfig& config, const opendnp3::DatabaseSizes& dbSizes = opendnp3::DatabaseSizes::Empty());

    size_t SendToOutstation(const std::string& hex);

    size_t LowerLayerUp();

    size_t LowerLayerDown();

    size_t OnTxReady();

    size_t NumPendingTimers() const;

    bool AdvanceToNextTimer();

    size_t AdvanceTime(const opendnp3::TimeDuration& td);

    MockLogHandler log;

    void Transaction(const std::function<void(opendnp3::IUpdateHandler&)>& apply)
    {
        // auto& handler = context.GetUpdateHandler();
        apply(context.GetUpdateHandler());
        context.CheckForTaskStart();
    }

private:
    const std::shared_ptr<exe4cpp::MockExecutor> exe;

public:
    const std::shared_ptr<MockLowerLayer> lower;
    const std::shared_ptr<MockCommandHandler> cmdHandler;
    const std::shared_ptr<MockOutstationApplication> application;
    opendnp3::OContext context;
};

#endif
