#ifndef _RPMSIGN_H
#define _RPMSIGN_H

/** \file sign/rpmsign.h
 *
 * Signature API
 */

#include <rpm/argv.h>
#include <rpm/rpmpgp.h>

#ifdef __cplusplus
extern "C" {
#endif

enum rpmSignFlags_e {
    RPMSIGN_FLAG_NONE		= 0,
    RPMSIGN_FLAG_IMA		= (1 << 0),
    RPMSIGN_FLAG_RPMV3		= (1 << 1),
    RPMSIGN_FLAG_FSVERITY	= (1 << 2),
};
typedef rpmFlags rpmSignFlags;

struct rpmSignArgs {
    char *keyid;
    pgpHashAlgo hashalgo;
    rpmSignFlags signflags;
    /* ... what else? */
};

/** \ingroup rpmsign
 * Sign a package
 * @param path		path to package
 * @param args		signing parameters (or NULL for defaults)
 * @return		0 on success
 */
int rpmPkgSign(const char *path, const struct rpmSignArgs * args);

/** \ingroup rpmsign
 * Delete signature(s) from a package
 * @param path		path to package
 * @param args		signing parameters (or NULL for defaults)
 * @return		0 on success
 */
int rpmPkgDelSign(const char *path, const struct rpmSignArgs * args);


/** \ingroup rpmsign
 * Delete file signature(s) from a package
 * @param path		path to package
 * @param args		signing parameters (or NULL for defaults)
 * @return		0 on success
 */
int rpmPkgDelFileSign(const char *path, const struct rpmSignArgs * args);

#ifdef __cplusplus
}
#endif

/**  \ingroup rpmsign
 * Generate GPG signature(s) for a header+payload file from all args.
 * @param sigh		signature header
 * @param ishdr		header-only signature?
 * @param fd		file descriptor data is read from
 * @param fileName	name of the file containing data to be signed
 * @param start		offset at which data is taken
 * @param size		size of the data to sign
 * @return		generated sigtag on success, 0 on failure
 */
rpmtd makeGPGSignatureArgs(Header sigh, int ishdr, FD_t fd,
			   const char *fileName, off_t start, rpm_loff_t size);
#endif /* _RPMSIGN_H */
