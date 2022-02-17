# aad_prt_bof

This bof allows Cobalt Strike to extract Azure AD PRT tokens from the machine.
These tokens can then be used with tools like ROADTools to extract AAD information.

## How to compile
`make` for the beacon object files

`make test` for an executable

## Usage

After compiling, load the `aadprt.cna` file into Cobalt Strike.

1. Request a nonce using ROADrecon: `roadrecon auth --prt-init`
2. Request a token on the target machine: `aadprt [NONCE]`
3. Use the token to authenticate in ROADrecon (or any other tool): `roadrecon auth --prt-cookie [TOKEN]`
4. Profit!

## References

Heavily inspired by the awesome work and research of [Dirk-jan](https://twitter.com/_dirkjan) and [Lee](http://twitter.com/tifkin_).

- https://dirkjanm.io/abusing-azure-ad-sso-with-the-primary-refresh-token/
- https://github.com/dirkjanm/ROADtoken
- https://github.com/leechristensen/RequestAADRefreshToken
- https://github.com/trustedsec/CS-Situational-Awareness-BOF
