# pip install pycryptodome

# 

from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256 as SHA
from Crypto.Signature import pkcs1_15

# 신뢰할만한 인증기관 클래스
class CertificateAuthority:
  def __init__(self, keysize = 2048):
    # 키사이즈가 keysize인 RSA 비밀키, 공개키 쌍 생성
    self.private_key = RSA.generate(keysize)
    self.public_key = self.private_key.publickey()

  def issueCertificate(self, bob_public_key):
    # cert_msg: 인증서에 적힐 메시지
    cert_msg = "Bob's public key is " + bob_public_key.exportKey().decode()

    # 인증기관의 비밀키(self.private_key)로 msg를 서명

    # 1. h = SHA(cert_msg) 계산
    h = SHA.new(cert_msg.encode())


    # 2. 인증기관의 비밀키로 서명 클래스 생성
    signer = pkcs1_15.new(self.private_key)


    # 3. 실제 서명: cert_sign 생성
    cert_sign = signer.sign(h)


    # 인증서(certificate)는 msg, sign_msg, 인증기관의 공개키로 이루어짐
    certificate = {}
    certificate['cert_msg'] = cert_msg
    certificate['cert_sign'] = cert_sign
    certificate['CA_pubkey'] = self.public_key

    return certificate
  

  #Alice 입장에서 Bob의 공개키와 인증서를 받아서 공개키와 인증서를 검증하는 부분

def verifyPublicKey(bob_public_key_path, certificate):
  # 인증서 (certificate) 딕셔너리에서 구성요소 가져오기
  cert_msg = certificate['cert_msg']
  cert_sign = certificate['cert_sign']
  CA_pubkey = certificate['CA_pubkey']

  # 인증기관의 공개키로 Bob의 공개키 검증하기

  # 1. h = SHA(cert_msg) 계산
  h = SHA.new(cert_msg.encode())


  # 2. 인증기관의 공개키로 검증 클래스 생성
  verifier = pkcs1_15.new(CA_pubkey)


  # 3. 최종 검증 (공개키암호 실습시 try, except 구문 참조)
  # 검증 성공시 "Bob's public key is valid!"
  # 검증 실패시 "Given public key is not Bob's one!" 출력
  try:
        verifier.verify(h, cert_sign)
        print("Bob's public key is valid!")
  except (ValueError, TypeError):
      print("Given public key is not Bob's one!")


bob_private_key = RSA.generate(1024)
bob_public_key = bob_private_key.publickey()

myCA = CertificateAuthority(2048)
certificate = myCA.issueCertificate(bob_public_key)

verifyPublicKey(bob_public_key, certificate)