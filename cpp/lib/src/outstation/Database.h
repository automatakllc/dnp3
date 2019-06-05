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
#ifndef OPENDNP3_DATABASE_H
#define OPENDNP3_DATABASE_H

#include "outstation/IDatabase.h"
#include "outstation/IEventReceiver.h"
#include "outstation/StaticDataMaps.h"

#include "opendnp3/outstation/DatabaseConfig.h"
#include "opendnp3/gen/AssignClassType.h"
#include "opendnp3/gen/IndexMode.h"

namespace opendnp3
{

/**
The database coordinates all updates of measurement data
*/
class Database final : public IDatabase, private Uncopyable
{
public:
    Database(const DatabaseConfig& config,
             IEventReceiver& event_receiver,             
             StaticTypeBitField allowed_class_zero_types);

    // ------- IDatabase --------------

    virtual bool Update(const Binary&, uint16_t, EventMode = EventMode::Detect) override;
    virtual bool Update(const DoubleBitBinary&, uint16_t, EventMode = EventMode::Detect) override;
    virtual bool Update(const Analog&, uint16_t, EventMode = EventMode::Detect) override;
    virtual bool Update(const Counter&, uint16_t, EventMode = EventMode::Detect) override;
    virtual bool Update(const FrozenCounter&, uint16_t, EventMode = EventMode::Detect) override;
    virtual bool Update(const BinaryOutputStatus&, uint16_t, EventMode = EventMode::Detect) override;
    virtual bool Update(const AnalogOutputStatus&, uint16_t, EventMode = EventMode::Detect) override;
    virtual bool Update(const OctetString& value, uint16_t index, EventMode mode = EventMode::Detect) override;
    virtual bool Update(const TimeAndInterval&, uint16_t) override;
    virtual bool Modify(FlagsType type, uint16_t start, uint16_t stop, uint8_t flags) override;

    // ------- Misc ---------------

    IResponseLoader& GetResponseLoader() override
    {
        return data_maps;
    }
    IStaticSelector& GetStaticSelector() override
    {
        return data_maps;
    }
    IClassAssigner& GetClassAssigner() override
    {
        return data_maps;
    }    

private:

	StaticDataMaps data_maps;
    IEventReceiver& event_receiver;    
   
    static bool ConvertToEventClass(PointClass pc, EventClass& ec);

    template<class Spec> bool UpdateEvent(const typename Spec::meas_t& value, uint16_t index, EventMode mode);

    //template<class Spec> bool UpdateAny(Cell<Spec>& cell, const typename Spec::meas_t& value, EventMode mode);

    template<class Spec> void TryCreateEvent(Cell<Spec>& cell, const typename Spec::meas_t& value);

    template<class Spec> bool Modify(uint16_t start, uint16_t stop, uint8_t flags);

    // stores the most recent values, selected values, and metadata
    
};

} // namespace opendnp3

#endif
