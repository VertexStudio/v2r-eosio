Eos = require('eosjs')

eos = Eos({ keyProvider: '5JPiMk1mJx3VLsBaSbNUxhMrMdxrFjR8VPpFPM8fikp4Mtu6CpE' })

async function test() {

    await eos.transaction(
        {
            actions: [
                {
                    account: 'v2r.notary',
                    name: 'addchallenge',
                    authorization: [{
                        actor: 'v2r.notary',
                        permission: 'owner'
                    }],
                    data: {
                        challengeid: 1000,
                        matchid: 2000,
                        streamerid: 3000,
                        description: 'who is female? (a) batman (b) superman (c) wonderwoman'
                    }
                }
            ]
        }
    )

    const responses = [
        [1000, 9010, "(a) batman"],
        [1000, 9011, "(b) superman"],
        [1000, 9012, "(c) wonderwoman"],
        [1000, 9013, "(a) batman"],
        [1000, 9014, "(b) superman"],
        [1000, 9015, "(c) wonderwoman"]
    ]

    let asyncResponse = async function (responses) {
        for (const response of responses) {
            await eos.transaction(
                {
                    actions: [
                        {
                            account: 'v2r.notary',
                            name: 'addresponse',
                            authorization: [{
                                actor: 'v2r.notary',
                                permission: 'owner'
                            }],
                            data: {
                                challengeid: response[0],
                                userid: response[1],
                                description: response[2]
                            }
                        }
                    ]
                }
            )
        }
    }

    await asyncResponse(responses)

    await eos.transaction(
        {
            actions: [
                {
                    account: 'v2r.notary',
                    name: 'endchallenge',
                    authorization: [{
                        actor: 'v2r.notary',
                        permission: 'owner'
                    }],
                    data: {
                        challengeid: 1000,
                        response: '(c) wonderwoman',
                        winners: [9012, 9015]
                    }
                }
            ]
        }
    )

}

test((error, result) => { console.log(error, result) })
