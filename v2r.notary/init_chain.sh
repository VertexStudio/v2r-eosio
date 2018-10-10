cleos wallet unlock -n debug --password PW5JGqrHwsAphXLGcZ4rHAJqQxmGQXdL42puB5Vjo14odGspwYFvo

# setup params
EOS_KEY=EOS8k4wDWyrq9yPUL17YKqThf5F5VVMs5c8diRZQfGKG9698dd6na

# v2r.notary account
echo "\nCreating v2r.notary account"
cleos create account eosio v2r.notary ${EOS_KEY} ${EOS_KEY}
cleos set contract v2r.notary ../v2r.notary -p v2r.notary



