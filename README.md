# C_libray_project
2024 프로그래밍응용및실습 팀과제.

## 주요파일 설명
1. **main.c**
   - 프로그램의 진입점으로, 초기 메뉴 출력 및 사용자 입력 처리.
   - 회원가입과 로그인으로 연결
2. **auth.**
   - 회원가입 및 로그인 로직 구현.
   - `sign_up()`, `sign_in()` 함수 정의.
3. **library.h**
   - 전체 사용하는 함수 선언.
   - `Client`, `Book`, `Borrow` 구조체 정의.
4. **utils.c**
   - 다양한 곳에서 쓰일 가능성이 있는 도구형 함수 정의
   - `print_menu_name()`, `get_string(출력할 문자, 입력받을배열)` 함수 정의.
   
## 설치방법
```bash
git clone https://github.com/nebulaBdj/C_library_project.git
cd C_library_project
