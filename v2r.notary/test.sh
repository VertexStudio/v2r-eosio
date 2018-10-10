cleos wallet unlock -n debug --password PW5JGqrHwsAphXLGcZ4rHAJqQxmGQXdL42puB5Vjo14odGspwYFvo

# add challenge
cleos push action v2r.notary addchallenge '[1000, 2000, 3000, "who is female? (a) batman (b) superman (c) wonderwoman"]' -p v2r.notary

# add responses
cleos push action v2r.notary addresponse '[1000, 9010, "(a) batman"]' -p v2r.notary
cleos push action v2r.notary addresponse '[1000, 9011, "(b) superman"]' -p v2r.notary
cleos push action v2r.notary addresponse '[1000, 9012, "(c) wonderwoman"]' -p v2r.notary
cleos push action v2r.notary addresponse '[1000, 9013, "(a) batman"]' -p v2r.notary
cleos push action v2r.notary addresponse '[1000, 9014, "(b) superman"]' -p v2r.notary
cleos push action v2r.notary addresponse '[1000, 9015, "(c) wonderwoman"]' -p v2r.notary

# end challenge
cleos push action v2r.notary endchallenge '[1000, "(c) wonderwoman", [9012, 9015]]' -p v2r.notary
