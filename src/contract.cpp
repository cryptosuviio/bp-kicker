/*
 * Copyright 2021 Ville Sundell/CRYPTOSUVI OSK
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <eosio/eosio.hpp>
#include <eosio/name.hpp>
#include <eosio.system/eosio.system.hpp>

#define MISSED_BLOCKS_THRESHOLD 50 /* Hardcoded missed blocks threshold */
#define KICKER_ROLE "bpkicker"_n

using namespace eosio;

class [[eosio::contract("contract")]] _contract : public eosio::contract {
   public:
      using eosio::contract::contract;

      [[eosio::action]]
      void kick(name bp) {
         eosiosystem::producers_table producers ("eosio"_n, "eosio"_n.value);

         auto& producer = producers.get(bp.value, "BP not found");

         check(producer.missed_blocks_per_rotation > MISSED_BLOCKS_THRESHOLD, "Not enough blocks missed");

         /* We don't need to check if the BP is active, eosio::unregprod() will do that for us. */
         eosiosystem::system_contract::unregprod_action unregprod("eosio"_n, {bp, KICKER_ROLE});
         unregprod.send(bp);
      }
};
