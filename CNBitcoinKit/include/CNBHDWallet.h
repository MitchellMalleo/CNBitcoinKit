//
//  CNBHDWallet.h
//  CNBitcoinKit
//
//  Created by BJ Miller on 1/20/18.
//  Copyright © 2018 Coin Ninja, LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CNBBaseCoin.h"
#import "CNBMetaAddress.h"
#import "CNBAddressResult.h"
#import "CNBitcoinKit.h"
#import "CNBCipherKeys.h"
#import "CNBEncryptionCipherKeys.h"
#import "CNBDerivationPath.h"

#define kLibbitcoinErrorCode @"error_code"
#define kLibbitcoinErrorMessage @"error_message"

NS_ASSUME_NONNULL_BEGIN

@interface CNBHDWallet : NSObject

@property (readonly) NSString * _Nonnull coinNinjaVerificationKeyHexString;
@property (nonatomic, strong) CNBBaseCoin *coin;

+ (nonnull NSArray <NSString *>*)allWords;

/// createMnemonicWordsWithEntropy
/// @param entropy bytes of secure random data, provided by client. On iOS, use SecRandomCopyBytes, at least 16 bytes.
/// @return An NSArray <NSString *>* of mnemonic words. Returns an empty array if the entropy fails validation. Suggest looping, providing new entropy, if returning an empty array.
+ (NSArray <NSString *> *)createMnemonicWordsWithEntropy:(NSData *)entropy;
+ (BOOL)addressIsBase58CheckEncoded:(NSString *)address;

- (instancetype)init;
- (instancetype)initWithCoin:(CNBBaseCoin *)coin;
- (instancetype)initWithEntropy:(NSData *)entropy;
- (instancetype)initWithCoin:(CNBBaseCoin *)coin entropy:(NSData *)entropy;
- (instancetype)initWithMnemonic:(NSArray *)mnemonicSeed coin:(CNBBaseCoin *)coin;

- (NSArray *)mnemonicWords;
- (CNBMetaAddress *)receiveAddressForIndex:(NSUInteger)index;
- (CNBMetaAddress *)changeAddressForIndex:(NSUInteger)index;

- (NSData *)signData:(NSData *)data;
- (NSString *)signatureSigningData:(NSData *)data;
- (BOOL)verifySignedData:(NSData *)data signature:(NSData *)signature;

/**
 Encyrption Cipher Keys for uncompressed ec public key

 @param publicKeyData data bytes of uncompressed ec public key
 @param entropy data bytes of secure random entropy provided by client
 @return A CNBCipherKeys object containing the encryption_key and hmac_key used for encrypting/decrypting a set of bytes.
 */
- (CNBEncryptionCipherKeys *)encryptionCipherKeysForPublicKey:(NSData *)publicKeyData withEntropy:(NSData *)entropy;

/**
 Encryption Cipher Keys for uncompressed ec public key, using default private key.

 @param publicKeyData data bytes of uncompressed ec public key
 @return A CNBCipherKeys object containing the encryption_key and hmac_key used for encrypting/decrypting a set of bytes.
*/
- (CNBEncryptionCipherKeys *)encryptionCipherKeysForPublicKey:(NSData *)publicKeyData;

- (CNBCipherKeys *)decryptionCipherKeysForDerivationPathOfPrivateKey:(CNBDerivationPath *)path
                                                           publicKey:(NSData *)publicKeyData;
- (CNBCipherKeys *)decryptionCipherKeysWithDefaultPrivateKeyForPublicKey:(NSData *)publicKeyData;

/**
 Checks for existence of address in a wallet, whether external or internal for the `change` index.

 @param address The address to check for.
 @param index The max index to check up to, not inclusive. This will scan indexes from 0 up to index.
 @return Returns an instance of `CNBAddressResult` if found, `nil` if not.
 */
- (CNBAddressResult * _Nullable)checkForAddress:(NSString * _Nonnull)address upToIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
