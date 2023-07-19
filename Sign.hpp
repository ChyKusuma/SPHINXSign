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
// The provided code implements the SPHINCS+ digital signature scheme and integrates it with a Merkle tree scheme implemented in "merkleblock.cpp". Let's break down the code and explain each component in detail:

  // addSignedTransactionToMerkleTree(const std::string& signedTransaction): This function is an interface function responsible for adding a signed transaction to the Merkle tree. It creates an instance of the MerkleBlock class from "merkleblock.cpp" and constructs the Merkle tree with the provided signed transaction.

  // generate_keypair(): This function generates a key pair using the SPHINCS+ key generation algorithm. It calls the generateKeyPair() function from the SPHINXKey namespace in "Key.cpp" to generate the key pair. The generated key pair is then converted from arrays to vectors and returned as a pair of vectors.

  // addSignedTransactionToMerkleTree(const std::string& signedTransaction): This function is another interface function responsible for adding a signed transaction to the Merkle tree. It extracts the signed transaction data, signature, and public key from the input. It then verifies the signature using the verify_data() function and if the verification is successful, creates a SignedTransaction object with the signed transaction data, signature, public key, and converted data vector. Finally, it adds the signed transaction to the Merkle tree instance using the addTransaction() function.

  // verify_data(const std::vector<uint8_t>& data, const std::string& signature, const uint8_t* public_key): This function is responsible for verifying the authenticity of the provided data using the SPHINCS+ verification algorithm. It calls the verify function from the sphincs_inner namespace with the provided data, signature, and public key. The function returns a boolean indicating whether the verification is successful or not.

  // verifySPHINXBlock(const Block& block, const std::string& signature, const PublicKey& public_key): This function verifies a given block in the SPHINX blockchain. It takes a block object, a signature, and a public key as input. It first verifies the block's signature using the verify_data() function. Then, it verifies the Merkle root of the block by calling the verifyMerkleRoot() function from the SPHINXMerkleBlock namespace in "merkleblock.cpp". The function returns a boolean indicating whether both the signature and Merkle root are valid.

  // verifySPHINXChain(const Chain& chain): This function verifies the integrity and consistency of a given SPHINX chain. It takes a chain object as input. It internally calls the verifyChainIntegrity() function, which checks the integrity and consistency of the chain by verifying each block and validating the chain's Merkle root. The function returns a boolean indicating whether the chain is valid.

// The code provides an interface for adding signed transactions to a Merkle tree and verifies the authenticity of the data using the SPHINCS+ digital signature scheme. It also includes functions to verify individual blocks and the entire chain in the SPHINX blockchain. The integration with the Merkle tree scheme allows for efficient verification and tamper detection of transactions in the blockchain.
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
#include "Key.hpp"
#include "Transaction.hpp"


namespace SPHINXSign {
    // Interface function to add a signed transaction to the Merkle tree in "merkleblock.cpp"
    void addSignedTransactionToMerkleTree(const std::string& signedTransaction, const uint8_t* privateKey) {
        // Get the signed transaction data, signature, and public key from the input
        std::string transactionData = extractTransactionData(signedTransaction);
        PublicKey publicKey = extractPublicKey(signedTransaction);

        // Sign the transaction data using the private key by calling the sign_data function from SPHINXVerify
        std::string signature = SPHINXVerify::sign_data(std::vector<uint8_t>(transactionData.begin(), transactionData.end()), privateKey);

        // Verify the signature before adding it to the Merkle tree
        if (!signature.empty() && verify_data(transactionData, signature, publicKey)) {
            SPHINXMerkleBlock::SignedTransaction signedTransaction;
            signedTransaction.transaction = transactionData;
            signedTransaction.signature = signature;
            signedTransaction.public_key = publicKey;
            signedTransaction.data = std::vector<uint8_t>(transactionData.begin(), transactionData.end());

            // Add the signed transaction to the Merkle tree
            SPHINXMerkleBlock::MerkleBlock::getInstance().addTransaction(signedTransaction);
        } else {
            // Signature verification failed or signature is empty, handle the error accordingly
            std::cerr << "ERROR: Invalid signature for transaction: " << signedTransaction << std::endl;
        }
    }

    // Function to verify data (unchanged)
    bool verify_data(const std::vector<uint8_t>& data, const std::string& signature, const uint8_t* public_key) {
        // Call the verification function from the inner namespace
        bool valid = sphincs_inner::verify<SPHINCS_N, SPHINCS_H, SPHINCS_D, SPHINCS_W, SPHINCS_V>(
            data.data(), data.size(), reinterpret_cast<const uint8_t*>(signature.data()), public_key);
        // Return the result of the verification
        return valid;
    }

    bool verifySPHINXBlock(const Block& block, const std::string& signature, const PublicKey& public_key) {
        // Step 1: Verify the signature of the block using the provided signature and public key
        bool isSignatureValid = SPHINXVerify::verifySPHINXBlock(block, signature, public_key);

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
