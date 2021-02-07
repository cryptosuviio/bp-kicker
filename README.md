# BP Kicker for Telos blockchain

Unlike other EOSIO chains, Telos system contract keeps track of missed block for every block producer.
Because of this unique feature, we can have a contract that can kick (if permitted by the BP) a BP when a certain threshold of missed blocks is reached.

## How BP Kicker works
When called, BP Kicker will check if missed blocks for this **rotation** (`missed_blocks_per_rotation`) for the specified BP has reached MISSED_BLOCKS_THRESHOLD (currectly hardcoded to `50`). If this condition is met, `eosio::unregprod` action will be called as `bpname@bpkicker`, and the BP is unregistered.

**Any blockchain user capable of issuing transactions on the network can call the contract and kick (if applicable) BPs that have enabled BP Kicker for their BP.**

## Enabling BP Kicker for your producer
To enable BP Kicker for your producer, you only need to create a permission named `bpkicker`, and allow the BP Kicker contract to use it.

To enable BP Kicker on Telos testnet:

`$ command here`

## Using BP Kicker
Any blockchain user capable of issuing transactions can call the `bpkicker::kick` action by:

`$ example command here`

## About the Author
**Ville Sundell** is the CTO of [CRYPTOSUVI](https://www.cryptosuvi.io/), a block producer on Telos.
