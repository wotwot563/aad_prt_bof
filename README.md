# aad_prt_bof

This bof allows Cobalt Strike to extract Azure AD PRT tokens from the machine.
These tokens can then be used with tools like ROADTools to extract AAD information.

### How to compile:
`make` for the beacon object files
`make test` for an executable

#### After compiling, load the (.cna) file to Cobalt Strike.

### Usage:
```
aadprt [nonce] 
```
