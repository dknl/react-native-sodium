
#include <jni.h>
#include "sodium.h"


#ifdef __cplusplus
extern "C" {
#endif

/* *****************************************************************************
 * Sodium-specific functions
 * *****************************************************************************
 */
JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_sodium_1init(JNIEnv *jenv, jclass jcls) {
  int result;
  result = (int)sodium_init();
  return (jint)result;
}

JNIEXPORT jstring JNICALL Java_org_libsodium_jni_SodiumJNI_sodium_1version_1string(JNIEnv *jenv, jclass jcls) {
  char *result = (char *)sodium_version_string();
  return (*jenv)->NewStringUTF(jenv, (const char *)result);
}



/* *****************************************************************************
 * Random data generation
 * *****************************************************************************
 */

JNIEXPORT jlong JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1random(JNIEnv *jenv, jclass jcls) {
  uint32_t result;
  result = (uint32_t)randombytes_random();
  return (jlong)result;
}

JNIEXPORT jlong JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1uniform(JNIEnv *jenv, jclass jcls, jlong j_upper_bound) {
  uint32_t result;
  result = (uint32_t)randombytes_uniform((uint32_t)j_upper_bound);
  return (jlong)result;
}

JNIEXPORT void JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1buf(JNIEnv *jenv, jclass jcls, jbyteArray j_buf, jint j_size) {
  unsigned char *buf = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_buf, 0);
  randombytes_buf(buf,(unsigned long long)j_size);
  (*jenv)->ReleaseByteArrayElements(jenv, j_buf, (jbyte *) buf, 0);
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1close(JNIEnv *jenv, jclass jcls) {
  int result = (int)randombytes_close();
  return (jint)result;
}

JNIEXPORT void JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1stir(JNIEnv *jenv, jclass jcls) {
  randombytes_stir();
}


/* *****************************************************************************
 * Secret-key cryptography - authenticated encryption
 * *****************************************************************************
 */
JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1keybytes(JNIEnv *jenv, jclass jcls) {
return  (jint)crypto_secretbox_KEYBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1noncebytes(JNIEnv *jenv, jclass jcls) {
return  (jint)crypto_secretbox_NONCEBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1macbytes(JNIEnv *jenv, jclass jcls) {
return (jint) crypto_secretbox_MACBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1easy(JNIEnv *jenv, jclass jcls, jbyteArray j_c, jbyteArray j_m, jlong j_mlen, jbyteArray j_n, jbyteArray j_k) {
  unsigned char *c = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_c, 0);
  unsigned char *m = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_m, 0);
  unsigned char *n = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_n, 0);
  unsigned char *k = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_k, 0);
  int result = crypto_secretbox_easy(c, m, (unsigned long long) j_mlen, n, k);
  (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *) c, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *) m, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *) n, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *) k, 0);
  return (jint)result;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1open_1easy(JNIEnv *jenv, jclass jcls, jbyteArray j_m, jbyteArray j_c, jlong j_clen, jbyteArray j_n, jbyteArray j_k) {
  unsigned char *m = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_m, 0);
  unsigned char *c = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_c, 0);
  unsigned char *n = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_n, 0);
  unsigned char *k = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_k, 0);
  int result = crypto_secretbox_open_easy(m, c, (unsigned long long)j_clen, n, k);
  (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *) m, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *) c, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *) n, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *) k, 0);
  return (jint)result;
}

/* *****************************************************************************
 * Secret-key cryptography - authentication
 * *****************************************************************************
 */
JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1auth_1bytes(JNIEnv *jenv, jclass jcls) {
  return (jint) crypto_auth_BYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1auth_1keybytes(JNIEnv *jenv, jclass jcls) {
  return (jint) crypto_auth_KEYBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1auth(JNIEnv *jenv, jclass jcls, jbyteArray j_out, jbyteArray j_in, jlong j_inlen, jbyteArray j_k) {
  unsigned char *out = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_out, 0);
  unsigned char *in = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_in, 0);
  unsigned char *k = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_k, 0);

  int result = crypto_auth(out,in,(unsigned long long) j_inlen,k);

  (*jenv)->ReleaseByteArrayElements(jenv, j_out, (jbyte *) out, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_in, (jbyte *) in, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *) k, 0);
  return (jint)result;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1auth_1verify(JNIEnv *jenv, jclass jcls, jbyteArray j_h, jbyteArray j_in, jlong j_inlen, jbyteArray j_k) {
  unsigned char *h = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_h, 0);
  unsigned char *in = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_in, 0);
  unsigned char *k = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_k, 0);

  int result = crypto_auth_verify(h, in, (unsigned long long) j_inlen, k);

  (*jenv)->ReleaseByteArrayElements(jenv, j_h, (jbyte *) h, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_in, (jbyte *) in, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *) k, 0);

  return (jint)result;
}

/* *****************************************************************************
 * Public-key cryptography - authenticated encryption
 * *****************************************************************************
 */
JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1publickeybytes(JNIEnv *jenv, jclass jcls) {
 return  (jint)crypto_box_PUBLICKEYBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1secretkeybytes(JNIEnv *jenv, jclass jcls) {
 return  (jint)crypto_box_SECRETKEYBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1noncebytes(JNIEnv *jenv, jclass jcls) {
 return  (jint)crypto_box_NONCEBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1macbytes(JNIEnv *jenv, jclass jcls) {
 return (jint) crypto_box_MACBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1zerobytes(JNIEnv *jenv, jclass jcls) {
 return (jint) crypto_box_ZEROBYTES;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1keypair(JNIEnv *jenv, jclass jcls, jbyteArray j_pk, jbyteArray j_sk) {
  unsigned char *pk = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_pk, 0);
  unsigned char *sk = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_sk, 0);
  int result = (int)crypto_box_keypair(pk, sk);
  (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *) pk, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *) sk, 0);
  return (jint)result;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1easy(JNIEnv *jenv, jclass jcls, jbyteArray j_c, jbyteArray j_m, jlong j_mlen, jbyteArray j_n, jbyteArray j_pk, jbyteArray j_sk) {
  unsigned char *c = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_c, 0);
  unsigned char *m = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_m, 0);
  unsigned char *n = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_n, 0);
  unsigned char *pk = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_pk, 0);
  unsigned char *sk = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_sk, 0);
  int result = crypto_box_easy(c, m, (unsigned long long) j_mlen, n, pk, sk);
  (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *) c, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *) m, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *) n, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *) pk, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *) sk, 0);
  return (jint)result;
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1open_1easy(JNIEnv *jenv, jclass jcls, jbyteArray j_m, jbyteArray j_c, jlong j_clen, jbyteArray j_n, jbyteArray j_pk, jbyteArray j_sk) {
  unsigned char *m = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_m, 0);
  unsigned char *c = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_c, 0);
  unsigned char *n = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_n, 0);
  unsigned char *pk = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_pk, 0);
  unsigned char *sk = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_sk, 0);
  int result = crypto_box_open_easy(m, c, (unsigned long long)j_clen, n, pk, sk);
  (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *) m, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *) c, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *) n, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *) pk, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *) sk, 0);
  return (jint)result;
}

#ifdef __cplusplus
}
#endif
