//
//  _   _         ______    _ _ _   _             _ _ _
// | \ | |       |  ____|  | (_) | (_)           | | | |
// |  \| | ___   | |__   __| |_| |_ _ _ __   __ _| | | |
// | . ` |/ _ \  |  __| / _` | | __| | '_ \ / _` | | | |
// | |\  | (_) | | |___| (_| | | |_| | | | | (_| |_|_|_|
// |_| \_|\___/  |______\__,_|_|\__|_|_| |_|\__, (_|_|_)
//                                           __/ |
//                                          |___/
// 
// This file is auto-generated. Do not edit manually
// 
// Copyright 2013-2019 Automatak, LLC
// 
// Licensed to Green Energy Corp (www.greenenergycorp.com) and Automatak
// LLC (www.automatak.com) under one or more contributor license agreements.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership. Green Energy Corp and Automatak LLC license
// this file to you under the Apache License, Version 2.0 (the "License"); you
// may not use this file except in compliance with the License. You may obtain
// a copy of the License at:
// 
//   http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "opendnp3/gen/FlowControl.h"

namespace opendnp3 {

uint8_t FlowControlToType(FlowControl arg)
{
  return static_cast<uint8_t>(arg);
}
FlowControl FlowControlFromType(uint8_t arg)
{
  switch(arg)
  {
    case(1):
      return FlowControl::Hardware;
    case(2):
      return FlowControl::XONXOFF;
    default:
      return FlowControl::None;
  }
}
char const* FlowControlToString(FlowControl arg)
{
  switch(arg)
  {
    case(FlowControl::Hardware):
      return "Hardware";
    case(FlowControl::XONXOFF):
      return "XONXOFF";
    default:
      return "None";
  }
}

}

namespace ser4cpp
{
  namespace serializers
  {
    template<>
    bool write_one(wseq_t& dest, const opendnp3::FlowControl& value)
    {
      return UInt8::write_to(dest, opendnp3::FlowControlToType(value));
    }

    template<>
    bool read_one(rseq_t& input, opendnp3::FlowControl& out)
    {
      UInt8::type_t tempFlowControl;
      bool result = UInt8::read_from(input, tempFlowControl);
      out = opendnp3::FlowControlFromType(tempFlowControl);
      return result;
    }
  }
}
