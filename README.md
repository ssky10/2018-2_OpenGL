# 2018학년도 2학기 OpenGL

- 수업교재 : [IT CookBook, OpenGL로 배우는 3차원 컴퓨터 그래픽스 - 한빛미디어](http://www.hanbit.co.kr/store/books/look.php?p_code=B1779572378)

## 00.Hello
   ![image](https://user-images.githubusercontent.com/7812961/62409838-556a2200-b618-11e9-8e87-8db977a1ebb8.png)

   OpenGL 첫 예제

## 01.Project1
   ![image](https://user-images.githubusercontent.com/7812961/62409864-9cf0ae00-b618-11e9-8714-341e9bc866b3.png)

   glShadeModel함수와 glColor3f함수를 이용한 도형그리기

## 02.Project2
   ![image](https://user-images.githubusercontent.com/7812961/62409915-1f796d80-b619-11e9-9dfb-af92ffb612d7.png)

   glutKeyboardFunc함수를 이용한 키보드 입력 이벤트 설정

    'R' : 색상 빨간색으로 변경
    'G' : 색상 초록색으로 변경
    'B' : 색상 파란색으로 변경
    'T' : 도형 삼각형으로 변경
    '+' : 도형 크기 증가
    '-' : 도형 크기 감소

## 03.Project3
   ![image](https://user-images.githubusercontent.com/7812961/62409968-1b9a1b00-b61a-11e9-9657-393a953ee5a8.png)

   glTranslatef, glScalef, glRotatef 함수를 이용하여 도형의 위치, 크기, 방향을 변경

## 04.Project4
   ![p4](https://user-images.githubusercontent.com/7812961/62410439-44bdaa00-b620-11e9-9a20-043126a8fd15.gif)

   gluLookAt함수를 통한 시점변환


## 05.Project5
- ### Code0606
   ![image](https://user-images.githubusercontent.com/7812961/62410265-7df51a80-b61e-11e9-82ab-4915879c7997.png)

- ### Code0606_2
   ![image](https://user-images.githubusercontent.com/7812961/62410327-260ae380-b61f-11e9-8473-6d7ffc4d6fb8.gif)

   glPushMatrix, glPopMatrix를 이용한 변환

## 06.Project6
- ### Culling
   ![image](https://user-images.githubusercontent.com/7812961/62410559-0fb25700-b622-11e9-9322-ef87bdd24f08.gif)

   GL_CULL_FACE를 이용한 후면제거 모드 활성/비활성, glFrontFace를 이용한 전면방향 설정

- ### Projection
   ![image](https://user-images.githubusercontent.com/7812961/62410595-83546400-b622-11e9-931a-57edffdeb2ee.png)

   glViewport를 이용한 화면투영 설정

## 07.Project7
- ### ClipPlane
   ![p7clip](https://user-images.githubusercontent.com/7812961/62412070-fae0be00-b637-11e9-8d72-31298fa684d2.gif)

   glClipPlane을 이용한 절단면 설정

- ### CullFace
   ![p7cull](https://user-images.githubusercontent.com/7812961/62413248-60d54180-b648-11e9-9c7a-4c8665053e2f.gif)
   
   glCullFace를 이용하여 전/후면 제거

## 08.Project8
- ### ImageSynthesis
   ![image](https://user-images.githubusercontent.com/7812961/62413445-1b197880-b64a-11e9-9b49-b0e866f29011.png)

- ### HiddenRemoval2
   ![p8](https://user-images.githubusercontent.com/7812961/62413497-764b6b00-b64a-11e9-9ae9-35e495e42ffb.gif)


## 09.Project9
- ### DrawLine
   ![image](https://user-images.githubusercontent.com/7812961/62413509-b7dc1600-b64a-11e9-96a2-e229831ebd12.png)

   glLineStipple를 이용한 다양한 패턴을 가지는 직선 생성

- ### Blend2
   ![p9](https://user-images.githubusercontent.com/7812961/62413552-3769e500-b64b-11e9-9a6d-4b8666c76682.gif)

   glBlendFunc를 이용하여 도형의 투명도(알파) 유무 설정


## 10.Project10
   ![image](https://user-images.githubusercontent.com/7812961/62413582-7a2bbd00-b64b-11e9-81b2-6ae04c08d306.png)

   glLightfv를 이용하여 주변(GL_AMBIENT)/확산(GL_DIFFUSE)/경면광(GL_SPECULAR) 설정


## 11.Project11
   ![p11](https://user-images.githubusercontent.com/7812961/62418299-a7ef2100-b6a0-11e9-8633-316ff82f6bcc.gif)

   조명이 고정되어 있을 때 물체의 위치/각도 와 시점의 위치에 따른 조명의 변화


## 12.Project12
- ### ManualTexture
   ![image](https://user-images.githubusercontent.com/7812961/62418340-6e6ae580-b6a1-11e9-8fc3-69bafaa1d521.png)

   glTexImage2D함수를 이용해 설정한 표면의 질감(패턴)을 glTexCoord2f함수를 이용해 수동으로 표현

- ### AutoTexture2D
   ![p12](https://user-images.githubusercontent.com/7812961/62418429-91969480-b6a3-11e9-91e4-bb9b2e8a0817.gif)

   glTexGeni, glTexGenfv, glEnable(GL_TEXTURE_GEN_S) 를 이용하여 표면의 질감표현을 자동으로 적용


## 13.FinalProject
   ![pf](https://user-images.githubusercontent.com/7812961/62418510-08805d00-b6a5-11e9-8ab4-5384e8227a28.gif)

   안드로이드 모양 그래픽을 이용한 승부차기 게임

   (참고자료 : OpenGL로 배우는 3차원 컴퓨터 그래픽스, 한빛미디어 - Project III 투상 변환 및 애니메이션)

    초록 안드로이드가 골대에 있을경우 유저가 선택한 방향은 안드로이드가 이동하는 방향(수비)가 되고, 노란 안드로이드가 골대에 있을경우 유저가 선택한 방향은 공이 이동하는 방향(공격)이다.
    방향을 먼저 선택한 후 공차기/막기(s)를 입력
    'q' : 왼쪽 상단
    'w' : 상단 중앙
    'e' : 오른쪽 상단
    'a' : 왼쪽 하단
    'd' : 오른쪽 하단
    's' : 공차기/막기
    'h' : 도움말

