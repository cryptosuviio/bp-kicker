# BP Kicker for Telos blockchain

Unlike other EOSIO chains, Telos system contract keeps track of missed block for every block producer.
Because of this unique feature, we can have a contract that can kick (if permitted by the BP) a BP when a certain threshold of missed blocks is reached.

## Read before use
**This is a tool of last resort**: if you are able to re-register during the same rotation, anyone can immediately `unregprod` you again, since your `missed_blocks_per_rotation` would be over the `MISSED_BLOCKS_THRESHOLD`. If you want to re-register during the same rotation you were kicked from using the BP Kicker, you may want temporarily remove the `bpkicker` permission. See "*Disabling BP Kicker for your producer*" for detailed instructions.

**Use only if your producer is stable enough to benefit from this**.

## How BP Kicker works
When called, BP Kicker will check if missed blocks for this **rotation** (`missed_blocks_per_rotation`) for the specified BP has reached MISSED_BLOCKS_THRESHOLD (currectly hardcoded to `50`). If this condition is met, `eosio::unregprod` action will be called as `bpname@bpkicker`, and the BP is unregistered.

**Any blockchain user capable of issuing transactions on the network can call the contract and kick (if applicable) BPs that have enabled BP Kicker for their BP.**

## Enabling BP Kicker for your producer
To enable BP Kicker for your producer, you only need to create a permission named `bpkicker`, and allow the BP Kicker contract to use it.

To enable BP Kicker, you need to run **both of these commands**:

`$ cleos set account permission cryptosuviio bpkicker bpkicker.com --add-code`

`$ cleos set action permission cryptosuviio eosio unregprod bpkicker`

> BP being `cryptosuviio` in this example. The contract is `bpkicker.com` on both, Testnet and Mainnet.

## Disabling BP Kicker for your producer
In case you need to disable BP Kicker, you can run the following commands:

`$ cleos set action permission cryptosuviio eosio unregprod NULL`

`$ cleos set account permission cryptosuviio bpkicker NULL`

> BP being `cryptosuviio` in this example.

## Using BP Kicker
Any blockchain user capable of issuing transactions can call the `bpkicker::kick` action by:

In order to kick `cryptosuviio` after over 50 missed blocks, anyone can run:

`$ cleos push action bpkicker.com kick ["cryptosuviio"] -p youraccountname`

> BP being `cryptosuviio` in this example. The contract is `bpkicker.com` on both, Testnet and Mainnet.

## Verifying the build
Build the contract by running `./build.sh`.

Contract is built with CDT 1.7.0, and resulting WASM SHA256 checksum is `71763ce35a58e3ea6244a028f1ef600d88393bde2d98fa165b7af0778364a187`.

## About the Author
**[Ville Sundell](https://www.linkedin.com/in/villesundell)** is the CTO of [CRYPTOSUVI](https://www.cryptosuvi.io/), a block producer on Telos.
