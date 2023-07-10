# SPHINXSign

## Introduction

This project is dedicated to the world community as an Open-source Post-quantum blockchain layer 1 project, means anyone can join and contribute based on his/ her passion and skills. SPHINX is a blockchain protocol designed to provide secure and scalable solutions in the post-quantum era.

This repository contains code for the SPHINXSign project, which is a Digital signature module for the SPHINX blockchain framework. The SPHINXSign aims to provide a `Signature scheme` in the blockchain systems.


## Components

#### This repository is part of [SPHINXMerkleBlock](https://github.com/SPHINX-HUB-ORG/SPHINXMerkleBlock)

The `SPHINXSign` namespace leverages the power of Merkle trees based on the state-of-the-art [SPHINCS+](https://sphincs.org/) principle, which emerged as the 4th winner in the "Post-Quantum" cryptography competition held by the National Institute of Standards and Technology ([NIST](https://www.nist.gov/publications/breaking-category-five-sphincs-sha-256)).

SPHINCS+ (Stateless PHotonic Isogeny-based Signature Scheme) is a groundbreaking hybrid signature scheme that combines robust hash-based, code-based, and isogeny-based cryptographic components. Its primary goal is to achieve two critical properties: "statelessness" and post-quantum security.

In the advent of quantum computers, which have the potential to render traditional cryptographic algorithms vulnerable, the elimination or reduction of reliance on state becomes imperative. Quantum computers, with their ability to exist in multiple states simultaneously, pose significant risks to storing sensitive content in state. The concept of "statelessness" in SPHINCS+ aims to mitigate these risks by eliminating the reliance on state, providing resilience against attacks by powerful quantum computers.

Unlike alternative post-quantum digital signature algorithms such as [Crystals-dilithium](https://pq-crystals.org/dilithium/), which offer high levels of security but are susceptible to side-channel attacks, our decision to employ SPHINCS+ as the foundation for our Merkle tree scheme and digital signature scheme ensures both the robustness against quantum adversaries and resistance to side-channel attacks.

With the `SPHINXSign` namespace, we empower developers to harness the advanced capabilities of SPHINCS+ and build secure, future-proof applications that can withstand the challenges posed by the dawn of the quantum era.

We know that Hash-Based digital signature scheme is not lattice-based and relly on the strengthness of the hash-function, thats why our default `SPHINX_256` hash function is based on SWIFFTX which is rely on "Lattice-based", here we try to achieve both `Statelessness` and `Lattice-based` at once.

Digital signature scheme like [Gottesman-chuang](https://www.researchgate.net/publication/2186040_Quantum_Digital_Signatures) its trully guarantee by Quantum-Laws, we aware about that, but it's still too expensive technology, its needed new infrastructure, new hardware, a lot of money will only spent into infrastructure, so for today its not solution for us and not applicable. One day, when the world already buld the quantum infrastructure i.e QKD we believed our construction will more safe.

## Lets breakdown their functionallity

- `addSignedTransactionToMerkleTree(const std::string& signedTransaction)`: 
  - This function serves as an interface to add a signed transaction to a Merkle tree, which is implemented in "merkleblock.cpp". 
  - It creates an instance of the `MerkleBlock` class from "merkleblock.cpp" and constructs the Merkle tree by passing the signed transaction as a parameter.

- `generate_keypair()`:
  - This function generates a key pair using the SPHINCS+ key generation algorithm.
  - It calls the `generateKeyPair()` function from the `SPHINXKey` namespace in "Key.cpp" to generate the key pair.
  - The generated key pair is then converted into vectors and returned as a pair.

- `addSignedTransactionToMerkleTree(const std::string& signedTransaction)`:
  - This function adds a signed transaction to the Merkle tree.
  - It extracts the transaction data, signature, and public key from the provided `signedTransaction`.
  - It then verifies the signature using the `verify_data` function.
  - If the verification is successful, it creates a `SignedTransaction` object with the signed transaction details and adds it to the Merkle tree instance using the `addTransaction()` function.
  - If the signature verification fails, it outputs an error message to `std::cerr`.

- `verify_data(const std::vector<uint8_t>& data, const std::string& signature, const uint8_t* public_key)`:
  - This function verifies the authenticity of the provided data using the SPHINCS+ verification algorithm.
  - It calls the `verify` function from the `sphincs_inner` namespace with the data, signature, and public key as parameters.
  - The function returns a boolean value indicating whether the verification is successful (`true`) or not (`false`).

- `verifySPHINXBlock(const Block& block, const std::string& signature, const PublicKey& public_key)`:
  - This function verifies a given block in the SPHINX blockchain.
  - It takes a `Block` object, a signature as a string, and a public key as input.
  - First, it verifies the signature of the block using the `verify_data` function.
  - Then, it verifies the Merkle root of the block by calling the `verifyMerkleRoot()` function from the `SPHINXMerkleBlock` namespace in "merkleblock.cpp".
  - The function returns `true` if both the signature and Merkle root are valid, and `false` otherwise.

- `verifySPHINXChain(const Chain& chain)`:
  - This function verifies the integrity and consistency of a given SPHINX chain.
  - It takes a `Chain` object as input.
  - It internally calls the `verifyChainIntegrity()` function, which checks the integrity and consistency of the chain by verifying each block and validating the chain's Merkle root.
  - The function returns `true` if the chain is valid, and `false` otherwise.



### Note

Every code in the repository is a part of the SPHINX blockchain algorithm, which is currently in development and not fully integrated or extensively tested for functionality. The purpose of this repository is to provide a framework and algorithm for the digital signature scheme in the SPHINX blockchain project.

As the project progresses, further updates and enhancements will be made to ensure the code's stability and reliability. We encourage contributors to participate in improving and refining the SPHINXBlock algorithm by submitting pull requests and providing valuable insights.

We appreciate your understanding and look forward to collaborative efforts in shaping the future of the SPHINX blockchain projec, to accelerating the construction we can find the specification of [SPHINCS+](https://github.com/SPHINX-HUB-ORG/SPHINXSign/blob/main/sphincs%2B-round3-specification.pdf).


## Getting Started
To get started with the SPHINX blockchain project, follow the instructions below:

1. Clone the repository: `git clone https://github.com/ChyKusuma/SPHINXSign.git`
2. Install the necessary dependencies (List the dependencies or provide a link to the installation guide).
3. Explore the codebase to understand the project structure and components.
4. Run the project or make modifications as needed.


## Contributing
We welcome contributions from the developer community to enhance the SPHINX blockchain project. If you are interested in contributing, please follow the guidelines below:

1. Fork the repository on GitHub.
2. Create a new branch for your feature or bug fix: `git checkout -b feature/your-feature-name` or `git checkout -b bugfix/your-bug-fix`.
3. Make your modifications and ensure the code remains clean and readable.
4. Write tests to cover the changes you've made, if applicable.
5. Commit your changes: `git commit -m "Description of your changes"`.
6. Push the branch to your forked repository: `git push origin your-branch-name`.
7. Open a pull request against the main repository, describing your changes and the problem it solves.
8. Insert your information (i.e name, email) in the authors space.

## License
Specify the license under which the project is distributed (MIT License).

## Contact
If you have any questions, suggestions, or feedback regarding the SPHINX blockchain project, feel free to reach out to us at [sphinxfounders@gmail.com](mailto:sphinxfounders@gmail.com).
