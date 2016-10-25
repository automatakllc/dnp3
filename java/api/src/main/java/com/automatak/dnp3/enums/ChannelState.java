/**
 * Copyright 2013-2016 Automatak, LLC
 *
 * Licensed to Automatak, LLC (www.automatak.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership. Automatak, LLC
 * licenses this file to you under the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
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
// Copyright 2013 Automatak LLC
// 
// Automatak LLC (www.automatak.com) licenses this file
// to you under the the Apache License Version 2.0 (the "License"):
// 
// http://www.apache.org/licenses/LICENSE-2.0.html
//

package com.automatak.dnp3.enums;
/**
* Enumeration for possible states of a channel
*/
public enum ChannelState
{
  /**
  * offline and idle
  */
  CLOSED(0),
  /**
  * trying to open
  */
  OPENING(1),
  /**
  * waiting to open
  */
  WAITING(2),
  /**
  * open
  */
  OPEN(3),
  /**
  * stopped and will never do anything again
  */
  SHUTDOWN(4);

  private final int id;

  public int toType()
  {
    return id;
  }

  ChannelState(int id)
  {
    this.id = id;
  }

  public static ChannelState fromType(int arg)
  {
    switch(arg)
    {
      case(0):
        return CLOSED;
      case(1):
        return OPENING;
      case(2):
        return WAITING;
      case(3):
        return OPEN;
      default:
        return SHUTDOWN;
    }
  }
}
