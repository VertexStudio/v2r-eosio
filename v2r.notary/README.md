# V2R Notary
Smart contract notarization of v2r challenges.


Init contract with:
```
$ make
$ ./init_node.sh
$ ./init_chain.sh
```

Test contract with cmd line:
```
$ ./test.sh
```

Or test contract with node:
```
$ npm test
```

Challenges:
```
$ cleos get table v2r.notary v2r.notary challenge
{
  "rows": [{
      "id": 1000,
      "matchid": 2000,
      "streamerid": 3000,
      "description": "who is female? (a) batman (b) superman (c) wonderwoman",
      "response": "(c) wonderwoman",
      "winners": [
        9012,
        9015
      ]
    }
  ],
  "more": false
}
```

Responses:
```
$ cleos get table v2r.notary v2r.notary response 
{
  "rows": [{
      "id": 0,
      "challengeid": 1000,
      "userid": 9010,
      "description": "(a) batman"
    },{
      "id": 1,
      "challengeid": 1000,
      "userid": 9011,
      "description": "(b) superman"
    },{
      "id": 2,
      "challengeid": 1000,
      "userid": 9012,
      "description": "(c) wonderwoman"
    },{
      "id": 3,
      "challengeid": 1000,
      "userid": 9013,
      "description": "(a) batman"
    },{
      "id": 4,
      "challengeid": 1000,
      "userid": 9014,
      "description": "(b) superman"
    },{
      "id": 5,
      "challengeid": 1000,
      "userid": 9015,
      "description": "(c) wonderwoman"
    }
  ],
  "more": false
}
```
