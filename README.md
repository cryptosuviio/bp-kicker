# BP Kicker for Telos blockchain

Unlike other EOSIO chains, Telos system contract keeps track of missed block for every block producer.
Because of this unique feature, we can have a contract that can kick (if permitted by the BP) a BP when a certain threshold of missed blocks is reached.

## Read before use
**This is a tool of last resort**: if you are able to re-register during the same rotation, anyone can immediately `unregprod` you again, since your `missed_blocks_per_rotation` would be over the `MISSED_BLOCKS_THRESHOLD`. If you want to re-register during the same rotation you were kicked from using the BP Kicker, you may want temporarily remove the `bpkicker` permission.

Also it's worth noting that on Telos `unregprod` can be called even when unregistered. This may lead to a ton of unregprod actions on your producer account after you have been kicked by the BP Kicker. However, this is only an aesthetic nuisance, since the caller pays for the resources, not you.

**Use only if your producer is stable enough to benefit from this**.

## How BP Kicker works
When called, BP Kicker will check if missed blocks for this **rotation** (`missed_blocks_per_rotation`) for the specified BP has reached MISSED_BLOCKS_THRESHOLD (currectly hardcoded to `50`). If this condition is met, `eosio::unregprod` action will be called as `bpname@bpkicker`, and the BP is unregistered.

**Any blockchain user capable of issuing transactions on the network can call the contract and kick (if applicable) BPs that have enabled BP Kicker for their BP.**

## Enabling BP Kicker for your producer
To enable BP Kicker for your producer, you only need to create a permission named `bpkicker`, and allow the BP Kicker contract to use it.

1. To enable BP Kicker on Telos testnet (BP being `cryptosuviio` in this example):
`$ cleos set account permission cryptosuviio bpkicker bpkicker1111 --add-code`

2. To restrict the @bpkicker role to "unregprod" only, you must run:
`$ cleos set action permission cryptosuviio eosio unregprod bpkicker`

## Using BP Kicker
Any blockchain user capable of issuing transactions can call the `bpkicker::kick` action by:

`$ cleos push action bpkicker1111 kick ["cryptosuviio"]`

## Verifying the build
Build the contract by running `./build.sh`.

Contract is built with CDT 1.7.0, and resulting WASM SHA256 checksum is `3f74ebe3407a3f7d20bbd071b9dd69dc62761f12ca631288ec50af123b7eedee`.

## About the Author
**Ville Sundell** is the CTO of [CRYPTOSUVI](https://www.cryptosuvi.io/), a block producer on Telos.
