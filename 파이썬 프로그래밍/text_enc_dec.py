w = open('code.txt','a',encoding='utf-8') #code.txt 파일 생성
w.close()

def encode(user): #2단계에서 수행할 암호화 함수. 인자=사용자가 입력한 파일명
    a = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789' #원래문자열
    a_list = [] #원래문자를 각각 담을 리스트
    a_list2 = [] #암호문자를 각각 담을 리스트
    for i in a:
        a_list.append(i)
        a_list2.append(i)
    import random
    random.shuffle(a_list2) #암호문자 리스트 만들기

    code_str = ''#암호문자열 (code.txt에 문자열 형태로 저장하기 위해)
    for i in range(62):
        code_str = code_str + a_list2[i]
    
    b = open(user,'r',encoding='utf-8')
    c = b.read()
    d = open(user,'w',encoding='utf-8')
    
    for i in c: #c라는 문자열에서 한글자씩 암호화 시작
        if i in a_list2: #i가 알파벳 or 숫자면
            n = 0
            while True: #i의 인덱스번호 n 찾기
                if a_list[n] == i:
                    break
                else:
                    n += 1
            i = a_list2[n] #암호리스트에서 찾아서 암호화하기
            d.write(i)
            
        else: #i가 한글이나 특수기호면
            d.write(i)
            
    w = open('code.txt','a',encoding='utf-8')
    w.write(user+'  '+code_str+'\n') #code.txt에 파일이름과 문자열 저장
    w.close()
            
    d.close()
    b.close()
    


def decode(user): #3단계에서 수행할 암호화 해제 함수. 인자=사용자가 입력한 파일명
    a = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789' #원래문자열

    
    code_str = file_name[user] #앞서 만든 딕셔너리에서 저장된 암호 문자열 가져오기
    a_list = [] #원래문자 리스트
    a_list2 = [] #암호문자 리스트
    for i in a:
        a_list.append(i)
    for i in code_str:
        a_list2.append(i)

    b = open(user,'r',encoding='utf-8')
    c = b.read()
    d = open(user,'w',encoding='utf-8')

    for i in c:
        if i in code_str:
            n = 0
            while True: #i의 인덱스번호 n 찾기
                if a_list2[n] == i:
                    break
                else:
                    n += 1
            i = a_list[n] #원래문자로 바꾸기
            d.write(i)
            
        else:
            d.write(i)

    del(file_name[user]) #file_name에서 삭제하기 (97번줄부터 정의될 딕셔너리)
    
    e = open('code.txt','w',encoding='utf-8') #삭제된 상태에서 다시 code.txt에 작성
    for i in file_name:
        e.write(i+'  '+file_name[i]) #i=키(파일이름), file_name[i]=밸류(암호문자열)
        
    e.close()
    d.close()
    b.close()







user = str(input('파일 이름.확장명을 입력하세요:')) #0단계

code = open('code.txt','r',encoding='utf-8')

file_name = {}
while True: #파일명 딕셔너리 만들기 (키로 파일이름 저장여부를 검사하기 위해)
    x = code.readline()
    if x == '': #code 다 읽었으면 반복문 종료
        break
    else:
        x = x.split() #파일명, 암호문자열 잘라서 리스트 만들기
        file_name[x[0]] = x[1] #키=파일명, 밸류=암호 문자열

if user in file_name: #3단계
    decode(user)
else: #2단계
    encode(user)

code.close()
