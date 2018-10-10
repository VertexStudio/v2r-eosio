#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/crypto.h>

using eosio::action;
using eosio::asset;
using eosio::const_mem_fun;
using eosio::indexed_by;
using eosio::key256;
using eosio::name;
using eosio::permission_level;
using eosio::print;

class notary : public eosio::contract
{
  public:
    notary(account_name self)
        : eosio::contract(self),
          challenges(_self, _self),
          responses(_self, _self)
    {
    }

    //@abi action
    void addchallenge(uint64_t challengeid, uint64_t matchid, uint64_t streamerid, const std::string &description)
    {
        auto new_challenge_itr = challenges.emplace(_self, [&](auto &challenge) {
            challenge.id = challengeid;
            challenge.matchid = matchid;
            challenge.streamerid = streamerid;
            challenge.description = description;
        });
    }

    //@abi action
    void addresponse(uint64_t challengeid, uint64_t userid, const std::string &description)
    {
        auto new_response_itr = responses.emplace(_self, [&](auto &response) {
            response.id = responses.available_primary_key();
            response.challengeid = challengeid;
            response.userid = userid;
            response.description = description;
        });
    }

    //@abi action
    void endchallenge(uint64_t challengeid, const std::string& response, const std::vector<uint64_t> &winners)
    {
        challenge_index existing_challenges(_self, _self);
        auto itr = existing_challenges.find(challengeid);
        eosio_assert(itr != existing_challenges.end(), "challenge doesn't exist");
        existing_challenges.modify(itr, _self, [&](auto &challenge) {
            eosio_assert(challenge.winners.begin() == challenge.winners.end(), "challenge already ended");
            challenge.response = response;
            challenge.winners = winners;
        });
    }

  private:
    //@abi table challenge i64
    struct challenge
    {
        uint64_t id;
        uint64_t matchid;
        uint64_t streamerid;
        std::string description;
        std::string response;
        std::vector<uint64_t> winners;

        uint64_t primary_key() const { return id; }

        uint64_t by_matchid() const { return matchid; }

        uint64_t by_streamerid() const { return streamerid; }

        EOSLIB_SERIALIZE(challenge, (id)(matchid)(streamerid)(description)(response)(winners))
    };

    typedef eosio::multi_index<N(challenge), challenge,
                               indexed_by<N(matchid), const_mem_fun<challenge, uint64_t, &challenge::by_matchid>>,
                               indexed_by<N(streamerid), const_mem_fun<challenge, uint64_t, &challenge::by_streamerid>>>
        challenge_index;

    challenge_index challenges;

    //@abi table response i64
    struct response
    {
        uint64_t id;
        uint64_t challengeid;
        uint64_t userid;
        std::string description;

        uint64_t primary_key() const { return id; }

        uint64_t by_challengeid() const { return challengeid; }

        uint64_t by_userid() const { return userid; }

        EOSLIB_SERIALIZE(response, (id)(challengeid)(userid)(description))
    };

    typedef eosio::multi_index<N(response), response,
                               indexed_by<N(challengeid), const_mem_fun<response, uint64_t, &response::by_challengeid>>,
                               indexed_by<N(userid), const_mem_fun<response, uint64_t, &response::by_userid>>>
        response_index;

    response_index responses;
};

EOSIO_ABI(notary, (addchallenge)(addresponse)(endchallenge))
