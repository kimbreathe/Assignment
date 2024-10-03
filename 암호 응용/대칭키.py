# pip install pycryptodome

import Crypto
from Crypto.Cipher import AES
from Crypto.Hash import SHA256 as SHA

class myAES():
  # 클래스 생성자
  def __init__(self, keytext, noncetxt, keysize = 128):
    hash_fn = SHA.new()
    hash_fn.update(keytext.encode('utf-8'))
    key = hash_fn.digest()
    keylen = int(keysize/8)
    self.key = key[:keylen]

    # self.nonce를 noncetxt의 해쉬값의 앞 8 바이트로 생성
    hash_fn.update(noncetxt.encode('utf-8'))
    iv = hash_fn.digest()
    self.iv = iv[:16]
    print('AES class is generated')

  # 메서드 1: 메시지 채움
  def makeEnabled(self, plaintext):
    # return 할 padded_plaintext 값 계산하기
    # hint : plaintext의 마지막 블록에서 남은 바이트 수를 계산하고, 이를 chr() 함수로 유니코드 형태로 변환하여 남은 바이트 수만큼 채워넣기
    fillersize = 0
    textsize = len(plaintext)
    if textsize % 16 != 0:
      fillersize = 16 - textsize%16
    filler = chr(fillersize)*fillersize
    header = '%d' %(fillersize)
    gap = 16 - len(header)
    header += '#'*gap
    padded_plaintext = header+plaintext+filler
    return padded_plaintext

  # 메서드 2: 메시지 암호화
  def encrypt(self, plaintext):
    # plaintext를 암호화한 encmsg 값 계산하기
    plaintext = self.makeEnabled(plaintext)
    aes = AES.new(self.key, AES.MODE_CBC, self.iv)
    encmsg = aes.encrypt(plaintext.encode())
    return encmsg

  # 메서드 3: 복호화 메시지에 대한 패딩 제거
  def decodePadding(self, dec_msg):
    # return할 decmsg (패딩 제거된 메시지) 계산하기
    header = dec_msg[:16].decode()
    fillersize = int(header.split('#')[0])
    if fillersize != 0:
      decmsg = dec_msg[16:-fillersize]
    else:
      decmsg = dec_msg[16:]
    return decmsg

  # 메서드 4: 암호문 복호화
  def decrypt(self, ciphertext):
    # ciphertext를 복호화한 dec_msg 값 계산하기
    aes = AES.new(self.key, AES.MODE_CBC, self.iv)
    dec_msg = aes.decrypt(ciphertext)
    return self.decodePadding(dec_msg)
  

##### 평가 코드
myaes = myAES('keytxdfg', 'nonce123')
msg1 = 'Hi, good luck for the final exam!!'
msg2 = 'Have a wonderful day!'

padded_msg1 = myaes.makeEnabled(msg1).encode()
padded_msg2 = myaes.makeEnabled(msg2).encode()

enc_msg1 = myaes.encrypt(msg1)
enc_msg2 = myaes.encrypt(msg2)
dec_msg1 = myaes.decrypt(enc_msg1)
dec_msg2 = myaes.decrypt(enc_msg2)

print(msg1)
print(padded_msg1)
print(enc_msg1)
print(dec_msg1.decode())

print(msg2)
print(padded_msg2)
print(enc_msg2)
print(dec_msg2.decode())