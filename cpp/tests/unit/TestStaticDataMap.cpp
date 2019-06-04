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

#include <opendnp3/app/MeasurementTypeSpecs.h>

#include <catch.hpp>
#include <outstation/StaticDataMap.h>

using namespace opendnp3;

#define SUITE(name) "StaticDataMap - " name

TEST_CASE(SUITE("update returns 'point_not_defined' for values that don't exist"))
{
    StaticDataMap<BinarySpec> map;
    REQUIRE(map.update(Binary(true), 0) == UpdateResult::point_not_defined);
}

TEST_CASE(SUITE("can only add points that aren't already defined"))
{
    StaticDataMap<BinarySpec> map{{{0, {}}}};

    REQUIRE_FALSE(map.add(Binary(), 0, BinaryConfig()));
}

TEST_CASE(SUITE("can detect events on existing point"))
{
    StaticDataMap<BinarySpec> map{{{0, {}}}};

    REQUIRE(map.update(Binary(true), 0) == UpdateResult::event);
    REQUIRE(map.update(Binary(true), 0) == UpdateResult::no_change);
}

TEST_CASE(SUITE("can select all points using default variation and iterate"))
{
    StaticDataMap<BinarySpec> map{{
        {0, {}},
        {3, {}},
        {7, {}},
    }};

    REQUIRE(map.get_selected_range().Count() == 0);
    REQUIRE(map.select_all() == 3);

    std::vector<StaticDataMap<BinarySpec>::iterator::value_type> items;
    for (auto& item : map)
    {
        items.push_back(item);
    }

    REQUIRE(items.size() == 3);
    for (auto& item : map)
    {
        REQUIRE(item.second.variation == BinarySpec::DefaultStaticVariation);
    }
}

TEST_CASE(SUITE("can select all points using specified variation and iterate"))
{
    const auto other_variation = StaticBinaryVariation::Group1Var1;

    REQUIRE(BinarySpec::DefaultStaticVariation != other_variation);

    StaticDataMap<BinarySpec> map{{
        {0, {}},
        {3, {}},
        {7, {}},
    }};

    REQUIRE(map.select_all(other_variation) == 3);

    std::vector<StaticDataMap<BinarySpec>::iterator::value_type> items;
    for (auto& item : map)
    {
        items.push_back(item);
    }

    REQUIRE(items.size() == 3);
    for (auto& item : map)
    {
        REQUIRE(item.second.variation == other_variation);
    }
}

TEST_CASE(SUITE("can select a range and iterate"))
{
    const auto other_variation = StaticBinaryVariation::Group1Var1;

    REQUIRE(BinarySpec::DefaultStaticVariation != other_variation);

    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {3, {}},
        {7, {}},
    }};

    REQUIRE(map.select(Range::From(0, 9)) == 3);
    const auto selected = map.get_selected_range();
    REQUIRE(selected.start == 1);
    REQUIRE(selected.stop == 7);

    std::vector<StaticDataMap<BinarySpec>::iterator::value_type> items;
    for (auto& item : map)
    {
        items.push_back(item);
    }

    REQUIRE(items.size() == 3);
}

TEST_CASE(SUITE("can select beyond the first entry"))
{
    const auto other_variation = StaticBinaryVariation::Group1Var1;

    REQUIRE(BinarySpec::DefaultStaticVariation != other_variation);

    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {3, {}},
        {7, {}},
    }};

    REQUIRE(map.select(Range::From(3, 8)) == 2);

    std::vector<StaticDataMap<BinarySpec>::iterator::value_type> items;
    for (auto& item : map)
    {
        items.push_back(item);
    }

    REQUIRE(items.size() == 2);
    REQUIRE(items[0].first == 3);
    REQUIRE(items[1].first == 7);
}

TEST_CASE(SUITE("iterating over part of the selection clears it"))
{
    const auto other_variation = StaticBinaryVariation::Group1Var1;

    REQUIRE(BinarySpec::DefaultStaticVariation != other_variation);

    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {3, {}},
        {7, {}},
    }};

    REQUIRE(map.select_all() == 3);

    // the first time through we increment entries for 1 and 3, but not 7
    for (auto& item : map)
    {
        if (item.first == 7)
        {
            break;
        }
    }

    // the second iteration there's only 7 remaining
    std::vector<StaticDataMap<BinarySpec>::iterator::value_type> items;
    for (auto& item : map)
    {
        items.push_back(item);
    }
    REQUIRE(items.size() == 1);
    REQUIRE(items[0].first == 7);
}

TEST_CASE(SUITE("iterating over the entire selection clears it"))
{
    const auto other_variation = StaticBinaryVariation::Group1Var1;

    REQUIRE(BinarySpec::DefaultStaticVariation != other_variation);

    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {3, {}},
        {7, {}},
    }};

    REQUIRE(map.select_all() == 3);

    // iterate through the entire selection
    for (auto& item : map)
    {
    }

    // the second iteration there's only 7 remaining
    std::vector<StaticDataMap<BinarySpec>::iterator::value_type> items;
    for (auto& item : map)
    {
        items.push_back(item);
    }
    REQUIRE(items.size() == 0);
}

TEST_CASE(SUITE("selecting a range that doesn't match anything return Range::Invalid"))
{
    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {7, {}},
    }};

    REQUIRE(map.select(Range::From(2, 6)) == 0);
    REQUIRE_FALSE(map.get_selected_range().IsValid());
}

TEST_CASE(SUITE("selecting the lower bound only returns a partial range"))
{
    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {7, {}},
    }};

    REQUIRE(map.select(Range::From(1, 6)) == 1);

    const auto selected = map.get_selected_range();
    REQUIRE(selected.start == 1);
    REQUIRE(selected.stop == 1);
}

TEST_CASE(SUITE("selecting the upper bound only returns a partial range"))
{
    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {7, {}},
    }};

    REQUIRE(map.select(Range::From(2, 8)) == 1);

    const auto selected = map.get_selected_range();
    REQUIRE(selected.start == 7);
    REQUIRE(selected.stop == 7);
}

TEST_CASE(SUITE("selecting the beyond the full range returns a partial range"))
{
    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {7, {}},
    }};

    REQUIRE(map.select(Range::From(0, 8)) == 2);

    const auto selected = map.get_selected_range();
    REQUIRE(selected.start == 1);
    REQUIRE(selected.stop == 7);
}

TEST_CASE(SUITE("can select disjoint ranges and iterate over them"))
{
    StaticDataMap<BinarySpec> map{{
        {1, {}},
        {2, {}},
        {5, {}},
        {9, {}},
    }};

    REQUIRE(map.select(Range::From(1, 3)) == 2);
    REQUIRE(map.select(Range::From(6, 9)) == 1);

    const auto selected = map.get_selected_range();
    REQUIRE(selected.start == 1);
    REQUIRE(selected.stop == 9);

    std::vector<StaticDataMap<BinarySpec>::iterator::value_type> items;
    for (auto& item : map)
    {
        items.push_back(item);
    }

    // doesn't include index 5
    REQUIRE(items.size() == 3);
    REQUIRE(items[0].first == 1);
    REQUIRE(items[1].first == 2);
    REQUIRE(items[2].first == 9);
}
