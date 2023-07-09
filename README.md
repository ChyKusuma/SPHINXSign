# SPHINXSign

## Introduction

This project is dedicated to the world community as an Open-source Post-quantum SPHINXSign blockchain, means anyone can join and contribute based on his/ her passion and skills. SPHINX is a blockchain protocol designed to provide secure and scalable solutions in the post-quantum era.

This repository contains code for the SPHINXSign project, which is a mining module for the SPHINX blockchain framework. The SPHINXSign aims to provide a “Signature scheme” in the blockchain systems.


## Components

The code defines the `SPHINXSign` namespace to encapsulate its functionality.

The code defines a function named `addSignedTransactionToMerkleTree` that takes a `const std::string&` parameter named `signedTransaction`. This function is intended as an interface function to add a signed transaction to a Merkle tree defined in "merkleblock.cpp". The function constructs the Merkle tree with the given signed transaction.

A `struct` named `KeyPair` is defined within the namespace. It contains two arrays: `secret_key` and `public_key`, each declared as `uint8_t` and with sizes defined by `sphincs_inner::SECRETKEY_BYTES` and `sphincs_inner::PUBLICKEY_BYTES` respectively.

A function named `generate_keypair` is defined. It generates a key pair using the `sphincs_inner::keygen` function from the inner namespace. The generated key pair is converted into vectors and returned as a pair.

Another function named `addSignedTransactionToMerkleTree` is defined within the namespace. This function takes a `const std::string&` parameter named `signedTransaction`. It extracts the transaction data, signature, and public key from the input. It then verifies the signature using the `verify_data` function and adds the signed transaction to the Merkle tree if the verification is successful. Otherwise, it outputs an error message to `std::cerr`.

A function named `verify_data` is defined within the namespace. It takes the data (as a `const std::vector<uint8_t>&`), signature (as a `const std::string&`), and public key (as a `const uint8_t*`). This function calls the `sphincs_inner::verify` function from the inner namespace to verify the data against the signature and public key.

Two more functions are defined within the namespace:

- `verifySPHINXBlock` takes a `const Block&`, a `const std::string&` signature, and a `const PublicKey&` public key as parameters. It verifies the signature of the block using the provided signature and public key, and then verifies the Merkle root of the block. It returns `true` if both verifications pass, and `false` otherwise.
- `verifySPHINXChain` takes a `const Chain&` chain as a parameter. It verifies the integrity and consistency of the chain. It returns `true` if the chain is valid, and `false` otherwise.


### This repository is part of the  [SPHINXMerkleBlock](https://github.com/SPHINX-HUB-ORG/SPHINXMerkleBlock)

Please note that the code in this repository is a part of the SPHINX blockchain algorithm, which is currently in development and not fully integrated or extensively tested for functionality. The purpose of this repository is to provide a framework and algorithm for the digital signature scheme in the SPHINX blockchain project.

As the project progresses, further updates and enhancements will be made to ensure the code's stability and reliability. We encourage contributors to participate in improving and refining the SPHINXBlock algorithm by submitting pull requests and providing valuable insights.

We appreciate your understanding and look forward to collaborative efforts in shaping the future of the SPHINX blockchain project.

## Getting Started
To get started with the SPHINX blockchain project, follow the instructions below:

1. Clone the repository: `git clone https://github.com/ChyKusuma/SPHINXChain.git`
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
