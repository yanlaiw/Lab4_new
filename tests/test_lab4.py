#!/usr/bin/env python3
"""Public integration tests for CSCE 313 Lab 4. No third-party packages."""
import os, socket, subprocess, time, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]

def free_port():
    s=socket.socket(); s.bind(('127.0.0.1',0)); p=s.getsockname()[1]; s.close(); return p

def run_case(mode, messages):
    port=free_port()
    server=subprocess.Popen([str(ROOT/'server'),str(port),mode],stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True)
    try:
        time.sleep(.15)
        if server.poll() is not None:
            raise AssertionError('server exited before client connected')
        text='\n'.join(messages+['quit'])+'\n'
        client=subprocess.run([str(ROOT/'client'),'127.0.0.1',str(port),mode],input=text,capture_output=True,text=True,timeout=4)
        try: out,err=server.communicate(timeout=4)
        except subprocess.TimeoutExpired: raise AssertionError('server did not exit after QUIT')
        assert client.returncode==0, f'client exit={client.returncode}, stderr={client.stderr}'
        assert server.returncode==0, f'server exit={server.returncode}, stderr={err}'
        for m in messages:
            assert f'ACK: {m}\n' in client.stdout, f'missing ACK for {m!r}; output={client.stdout!r}'
        assert 'BYE\n' in client.stdout, 'missing BYE'
    finally:
        if server.poll() is None: server.kill(); server.communicate()

def run_crypto_unit():
    # Compile a tiny independent check of exported crypto functions.
    import tempfile
    code=r'''#include "crypto.h"
#include <cassert>
int main(){
  assert(xorCipher(xorCipher("HELLO",7),7)=="HELLO");
  assert(xorCipher("HELLO",7)!="HELLO");
  assert(modPow(7,3,55)==13);
  assert(rsaEncrypt(7,3,55)==13);
  assert(rsaDecrypt(13,27,55)==7);
  return 0;
}'''
    with tempfile.TemporaryDirectory() as tmp:
        p=Path(tmp); (p/'check.cpp').write_text(code)
        build=subprocess.run(['g++','-std=c++17','-I',str(ROOT),str(p/'check.cpp'),str(ROOT/'crypto.cpp'),'-o',str(p/'check')],capture_output=True,text=True)
        assert build.returncode==0, build.stderr
        result=subprocess.run([str(p/'check')],capture_output=True,text=True,timeout=4)
        assert result.returncode==0, 'crypto unit check failed'

def main():
    cases=[('TCP plain messaging',lambda:run_case('plain',['Hello','How are you?','Message 3'])),
           ('XOR encrypt/decrypt',run_crypto_unit),
           ('TCP XOR messaging',lambda:run_case('xor',['Hello','A message with spaces','12345'])),
           ('TCP RSA hybrid messaging',lambda:run_case('hybrid',['Hello','RSA + XOR','Last message']))]
    passed=0
    for name,fn in cases:
        try: fn(); print('[PASS]',name); passed+=1
        except Exception as e: print('[FAIL]',name,'-',e)
    print(f'Passed {passed}/{len(cases)} public checks')
    return 0 if passed==len(cases) else 1
if __name__=='__main__':sys.exit(main())
