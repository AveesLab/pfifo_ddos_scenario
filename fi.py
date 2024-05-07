from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.asymmetric import padding
import os

def generate_rsa_keys():
    # 2048비트 RSA 키 쌍 생성
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
    )

    # 개인키를 PEM 형식으로 저장
    with open("private_key.pem", "wb") as f:
        f.write(
            private_key.private_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PrivateFormat.TraditionalOpenSSL,
                encryption_algorithm=serialization.NoEncryption()
            )
        )

    # 공개키 추출
    public_key = private_key.public_key()

    # 공개키를 PEM 형식으로 저장
    with open("public_key.pem", "wb") as f:
        f.write(
            public_key.public_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PublicFormat.SubjectPublicKeyInfo
            )
        )

def sign_data():
    # 개인키 로드
    with open("private_key.pem", "rb") as key_file:
        private_key = serialization.load_pem_private_key(
            key_file.read(),
            password=None
        )

    # 데이터 준비
    data = "123".encode()

    # 데이터 서명
    signature = private_key.sign(
        data,
        padding.PKCS1v15(),
        hashes.SHA256()
    )

    # 서명을 파일로 저장
    with open("signature.bin", "wb") as f:
        f.write(signature)

# 함수 실행
generate_rsa_keys()
sign_data()
