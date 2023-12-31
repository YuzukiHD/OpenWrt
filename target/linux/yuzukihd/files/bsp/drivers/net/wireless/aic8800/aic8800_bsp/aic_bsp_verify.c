#include <linux/kernel.h>
#include <linux/string.h>

/****************************** MACROS ******************************/
#define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))
#define CH(x, y, z)    (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z)   (((x) & (y)) ^  ((x) & (z)) ^ ((y) & (z)))
#define EP0(x)         (ROTRIGHT(x,  2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x)         (ROTRIGHT(x,  6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x)        (ROTRIGHT(x,  7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x)        (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

/**************************** VARIABLES *****************************/
static const uint32_t k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

struct sha256_ctx {
	uint8_t data[64];   /* current 512-bit chunk of message data, just like a buffer */
	uint32_t datalen;   /* sign the data length of current chunk */
	uint64_t bitlen;    /* the bit length of the total message */
	uint32_t state[8];  /* store the middle state of hash abstract */
};

/*********************** FUNCTION DEFINITIONS ***********************/
static void sha256_transform(struct sha256_ctx *ctx, const uint8_t *data)
{
	uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	/* initialization */
	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) |
			(data[j + 2] << 8) | (data[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
}

static void sha256_init(struct sha256_ctx *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

static void sha256_update(struct sha256_ctx *ctx, const uint8_t *data, size_t len)
{
	uint32_t i;

	for (i = 0; i < len; ++i) {
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64) {
			/* 64 byte = 512 bit  means the buffer ctx->data has
			 * fully stored one chunk of message,
			 * so do the sha256 hash map for the current chunk.
			 */
			sha256_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
}

static void sha256_final(struct sha256_ctx *ctx, uint8_t *hash)
{
	uint32_t i;

	i = ctx->datalen;

	/* Pad whatever data is left in the buffer. */
	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;  /* pad 10000000 = 0x80 */
		while (i < 56)
			ctx->data[i++] = 0x00;
	} else {
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha256_transform(ctx, ctx->data);
		memset(ctx->data, 0, 56);
	}

	/* Append to the padding the total message's length in bits and transform. */
	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha256_transform(ctx, ctx->data);

	/* copying the final state to the output hash(use big endian). */
	for (i = 0; i < 4; ++i) {
		hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

static int hmac_sha256(const uint8_t *plaintext, ssize_t psize, uint8_t *output)
{
	struct sha256_ctx ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, plaintext, psize);
	sha256_final(&ctx, output);
	return 0;
}

static int data_encrypt(uint8_t *din, uint8_t *dout)
{
	uint8_t sha[32], buf[36], tmp[12], i;
	int ret = hmac_sha256(din, 4, sha);
	if (ret)
		return ret;

	for (i = 0; i < 4; i++) {
		memcpy(&buf[i*9], &sha[i*8], 8);
		buf[i*9+8] = din[i];
	}

	for (i = 0; i < 12; i++)
		tmp[i] = MAJ(buf[3*i], buf[3*i + 1], buf[3*i + 2]);

	for (i = 0; i < 4; i++)
		dout[i] = CH(tmp[3*i], tmp[3*i + 1], tmp[3*i + 2]);
	return ret;
}

static int data_confucion(uint8_t *din, uint8_t *dout)
{
	uint8_t sha[32], buf[36], tmp[4], i;
	int ret = hmac_sha256(din, 4, sha);
	if (ret)
		return ret;

	for (i = 0; i < 4; i++) {
		memcpy(&buf[i*9], &sha[i*8], 8);
		buf[i*9+8] = din[i];
	}

	for (i = 0; i < 12; i++)
		dout[i] = CH(buf[3*i], buf[3*i + 1], buf[3*i + 2]);

	for (i = 0; i < 4; i++) {
		tmp[i]  = MAJ(dout[3*i], dout[3*i + 1], dout[3*i + 2]);
		dout[12+i] = tmp[i] ^ din[i];
	}
	return ret;
}

static int data_deconfucion(uint8_t *din, uint8_t *dout)
{
	uint8_t buf[16], tmp[4], i;
	int ret;
	for (i = 0; i < 4; i++) {
		tmp[i] = MAJ(din[3*i], din[3*i + 1], din[3*i + 2]);
		dout[i] = tmp[i] ^ din[12+i];
	}

	ret = data_confucion(dout, buf);
	if (ret)
		return ret;

	return memcmp(din, buf, 16) != 0;
}

extern int sunxi_get_soc_chipid(uint8_t *);
static __attribute__((weakref("sunxi_get_soc_chipid"))) int platform_verify(uint8_t *id);

int wcn_bind_verify_calculate_verify_data(uint8_t *din, uint8_t *dout)
{
	uint8_t random[4], encrypt[4], id[16];
	int ret = 0;
	memset(dout, 0, 16);
	ret = platform_verify(id);
	if (ret)
		return ret;

	ret = data_deconfucion(din, random);
	if (ret)
		return ret;

	ret = data_encrypt(random, encrypt);
	if (ret)
		return ret;

	ret = data_confucion(encrypt, dout);
		return ret;

	return 0;
}

