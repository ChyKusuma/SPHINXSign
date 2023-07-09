/*
 *  Copyright (c) (2023) SPHINX_ORG
 *  Authors:
 *    - (C kusuma) <thekoesoemo@gmail.com>
 *      GitHub: (https://github.com/chykusuma)
 *  Contributors:
 *    - (Contributor 1) <email1@example.com>
 *      Github: (https://github.com/yourgit)
 *    - (Contributor 2) <email2@example.com>
 *      Github: (https://github.com/yourgit)
 */


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// This code defines a namespace SPHINXSign which contains functions related to generating key pairs, signing data, and verifying signatures using the SPHINCS+ cryptographic scheme.

  // The code defines a struct KeyPair containing two arrays: secret_key and public_key. These arrays store the secret key and public key, respectively, used in the SPHINCS+ cryptographic scheme.

  // generate_keypair() is a function that generates a key pair using the SPHINCS+ key generation function from the inner namespace (sphincs_inner). The function returns the key pair as a pair of vectors: the secret key as std::vector<uint8_t> and the public key as std::vector<uint8_t>.

// sign_data() is a function used to sign data. It takes three parameters:

  // data: A std::vector<uint8_t> containing the data to be signed.
  // secret_key: A pointer to the secret key (raw array of bytes).
  // verifier_public_key: A pointer to the verifier's public key (raw array of bytes).
  // The function calculates the signature using the SPHINCS+ signing function from the inner namespace and then forwards the signature and verifier's public key to the verifier (presumably, the SPHINXVerify::verify_data function) for further verification. It returns the signature as a string.
  
// verify_data() is a function used to verify the signature of the data. It takes three parameters:

  // data: A std::vector<uint8_t> containing the data whose signature needs to be verified.
  // signature: A string containing the signature of the data.
  // public_key: A pointer to the public key (raw array of bytes) of the signer.
  // The function verifies the signature using the SPHINCS+ verification function from the inner namespace and returns a boolean indicating whether the signature is valid (true) or not (false).

// verifySPHINXBlock() is a function used to verify a given block in the SPHINX blockchain. It takes three parameters:

  // block: A Block object representing the block to be verified.
  // signature: A string containing the signature of the block.
  // public_key: A PublicKey object representing the public key of the signer.

// The function performs two verification steps:
  // Step 1: Verify the signature of the block using the provided signature and public key by calling the verify_data() function.
  // Step 2: Verify the Merkle root of the block using the SPHINXMerkleBlock::verifyMerkleRoot() function.
  // The function returns true if both verification steps are successful; otherwise, it returns false.

// verifySPHINXChain() is a function used to verify the entire SPHINX blockchain. It takes a Chain object as a parameter. The function performs the following steps:

  // Step 1: Verify the integrity and consistency of the chain by calling verifyChainIntegrity(chain).
  // Step 2: Execute the protocol to verify the chain by calling executeChainVerificationProtocol(chain).
  // The function returns true if both steps are successful; otherwise, it returns false.

// In summary, this code provides functions to generate key pairs, sign data, and verify signatures using the SPHINCS+ cryptographic scheme. The actual implementations of the SPHINCS+ cryptographic functions (such as key generation, signing, and verification) are assumed to be provided in the sphincs_inner namespace.
/////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef SIGN_HPP
#define SIGN_HPP

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Lib/Sphincs/include/sphincs_inner.hpp"
#include "Lib/Sphincs/include/hashing.hpp"
#include "Checksum.hpp"
#include "Hash.hpp"
#include "Verify.hpp"
#include "MerkleBlock.hpp"
#include "Chain.hpp"


namespace SPHINXSign {
    // Interface function to add a signed transaction to the Merkle tree in "merkleblock.cpp"
    void addSignedTransactionToMerkleTree(const std::string& signedTransaction) {
        SPHINXMerkleBlock::MerkleBlock merkleBlock;
        // Construct the Merkle tree with the signed transaction
        merkleBlock.constructMerkleTree({signedTransaction});
    }

    struct KeyPair {
        uint8_t secret_key[sphincs_inner::SECRETKEY_BYTES];
        uint8_t public_key[sphincs_inner::PUBLICKEY_BYTES];
    };

    // Function to generate a key pair
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> generate_keypair() {
        KeyPair keypair;
        // Call the key generation function from the inner namespace
        sphincs_inner::keygen<SPHINCS_N, SPHINCS_H, SPHINCS_D, SPHINCS_W, SPHINCS_V>(keypair.secret_key, keypair.public_key);

        // Convert the key pair arrays to vectors
        std::vector<uint8_t> secret_key(keypair.secret_key, keypair.secret_key + sphincs_inner::SECRETKEY_BYTES);
        std::vector<uint8_t> public_key(keypair.public_key, keypair.public_key + sphincs_inner::PUBLICKEY_BYTES);

        // Return the key pair as a pair of vectors
        return { secret_key, public_key };
    }

    // Interface function to add a signed transaction to the Merkle tree in "merkleblock.cpp"
    void addSignedTransactionToMerkleTree(const std::string& signedTransaction) {
        // Get the signed transaction data, signature, and public key from the input
        std::string transactionData = extractTransactionData(signedTransaction);
        std::string signature = extractSignature(signedTransaction);
        PublicKey publicKey = extractPublicKey(signedTransaction);

        // Verify the signature before adding it to the Merkle tree
        if (verify_data(transactionData, signature, publicKey)) {
            SPHINXMerkleBlock::SignedTransaction signedTrx;
            signedTrx.transaction = signedTransaction;
            signedTrx.signature = signature;
            signedTrx.public_key = publicKey;
            signedTrx.data = std::vector<uint8_t>(transactionData.begin(), transactionData.end());

            // Add the signed transaction to the Merkle tree
            SPHINXMerkleBlock::MerkleBlock::getInstance().addTransaction(signedTrx);
        } else {
            // Signature verification failed, handle the error accordingly
            std::cerr << "ERROR: Invalid signature for transaction: " << signedTransaction << std::endl;
        }
    }

    // Function to verify data
    bool verify_data(const std::vector<uint8_t>& data, const std::string& signature, const uint8_t* public_key) {
        // Call the verification function from the inner namespace
        bool valid = sphincs_inner::verify<SPHINCS_N, SPHINCS_H, SPHINCS_D, SPHINCS_W, SPHINCS_V>(
            data.data(), data.size(), reinterpret_cast<const uint8_t*>(signature.data()), public_key);
        // Return the result of the verification
        return valid;
    }

    bool verifySPHINXBlock(const Block& block, const std::string& signature, const PublicKey& public_key) {
        // Step 1: Verify the signature of the block using the provided signature and public key
        bool isSignatureValid = SPHINXSign::verify_data(block.getData(), signature, public_key);

        // Step 2: Verify the Merkle root of the block
        bool isMerkleRootValid = SPHINXMerkleBlock::verifyMerkleRoot(block.getMerkleRoot(), block.getTransactions());

        // Return the verification result
        return isSignatureValid && isMerkleRootValid;
    }

    bool verifySPHINXChain(const Chain& chain) {
        // Step 1: Verify the integrity and consistency of the chain
        bool isChainValid = verifyChainIntegrity(chain);

        // Return the verification result
        return isChainValid;
    }
} // namespace SPHINXSign

#endif // SIGN_HPP