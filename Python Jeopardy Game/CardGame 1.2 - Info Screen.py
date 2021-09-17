#Gabriela Shamblin
#6/21/21
#Card Game

import pygame, sys
from pygame.locals import *
import random
import QuestionFile

#Initilze and display
pygame.init()
WIDTH = 1000
HEIGHT = 600
DISPLAY = pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Cards")

#Colors
BLACK = pygame.Color(0,0,0)
WHITE = pygame.Color(255,255,255)
RED = pygame.Color(254,39,18)
ORANGE = pygame.Color(251,153,2)
YELLOW = pygame.Color(254,254,51)
GREEN = pygame.Color(0,255,0)
DARKGREEN = pygame.Color(0,150,0)
BLUE = pygame.Color(2,71,254)
PURPLE = pygame.Color(134,1,175)
PINK = pygame.Color(255,92,205)
colors = [BLACK,RED,ORANGE,YELLOW,GREEN,BLUE,PURPLE,PINK]
colorIndex = 0

#Score, questions, titles, ect.
score = 0
answeredCorrect = 0
answered = 0
startTitle = pygame.font.SysFont("yugothicyugothicuisemiboldyugothicuibold",50)
titleFont = pygame.font.SysFont("bodoniblack", 100)
questionFont = pygame.font.SysFont("yugothicyugothicuisemiboldyugothicuibold",50)
cardFont = pygame.font.SysFont("yugothicyugothicuisemiboldyugothicuibold",20)
questions = QuestionFile.questionList

#Card creation
cards = []
cardWidth = 200
cardHeight = 100
startX = 90
startY = 150
x = startX
y = startY
q = 0
for i in range(0, 4):
    for j in range(0, 4):
        cards.append([x, y, questions[q], True])
        y += cardHeight + 10
        q += 1
    y = startY
    x += cardWidth + 10

#Option card creation
optionCoords = []
optionWidth = 300
optionHeight = 100
optionStartX = 200
optionStartY = 350
optionX = optionStartX
optionY = optionStartY
o = 0
for i in range(0, 2):
    for j in range(0, 2):
        optionCoords.append([optionX, optionY])
        optionY += optionHeight + 10
        o += 1
    optionY = optionStartY
    optionX += optionWidth + 10



#---Functions---
#Check which box was clicked
def mainMenuClicked(x, y):
    x -= startX
    y -= startY
    x //= cardWidth
    y //= cardHeight

    if x>=0 or x<4 and y>=0 or y<4:
        box = (x * 4) + y
        return box
    else:
        return -1

#Check which box was clicked
def questionMenuClicked(x, y):
    x -= optionStartX
    y -= optionStartY
    x //= optionWidth
    y //= optionHeight

    if (x>=0 or x<2) and (y>=0 or y<2):
        box = (x * 2) + y
        return box
    else:
        return -1

#Get random answers to put on the question slide
def grabRandomAnswers(current):
    answerOptions = ["","",""]
    grabOption = 0
    for i in range(0,3):
        grabOption = random.randint(0,15)
        #Keep going if we get our current answer
        while questions[grabOption][1] == current:
            grabOption = random.randint(0,15)
        answerOptions[i] = questions[grabOption][1]
    return answerOptions

#Add to score based on correct answers
def calculateScore():
    global score
    global answeredCorrect
    
    if answeredCorrect == 0:
        return score
    elif answeredCorrect < 4:
        score += 10
    elif answeredCorrect < 8:
        score += 20
    elif answeredCorrect < 12:
        score+= 30
    else:
        score += 40
    return score
   


#---Screen Functions---
#The information screen
def infoScreen():
    screen = True
    while screen:
        for event in pygame.event.get():
            if event.type == QUIT:
                screen = False
            if event.type == KEYDOWN:
                if event.key == K_SPACE:
                    screen = False
        #Title at the top
        DISPLAY.fill(WHITE)
        title = startTitle.render("Triva Game Information",True,BLACK)
        titleRect = title.get_rect(center=(WIDTH/2,70))
        titleRect2 = title.get_rect(center=((WIDTH/2)-3,68))
        DISPLAY.blit(title,titleRect)
        DISPLAY.blit(startTitle.render("Triva Game Information",True,GREEN),titleRect2)

        #Info strings
        info = "To play, click on the question square you want to answer. You will be directed to the"
        info2 = "question's screen. Click on the answer you think is correct and another screen will tell"
        info3 = "you if you were right. The question screens will always have the correct answer and 3"
        info4 = "randomized answers from other questions. The amount of questions you got right are"
        info5 = "in the top left corner, your score is in the top right corner."

        #Info renders
        infoPic = cardFont.render(info,True,BLACK)
        infoPic2 = cardFont.render(info2,True,BLACK)
        infoPic3 = cardFont.render(info3,True,BLACK)
        infoPic4 = cardFont.render(info4,True,BLACK)
        infoPic5 = cardFont.render(info5,True,BLACK)

        #Info rectangles
        infoRect = infoPic.get_rect(center=(WIDTH/2,HEIGHT/2 - 60))
        infoRect2 = infoPic2.get_rect(center=(WIDTH/2,HEIGHT/2 - 30))
        infoRect3 = infoPic3.get_rect(center=(WIDTH/2,HEIGHT/2))
        infoRect4 = infoPic4.get_rect(center=(WIDTH/2,HEIGHT/2 + 30))
        infoRect5 = infoPic5.get_rect(center=(WIDTH/2,HEIGHT/2 + 60))

        #Info display
        DISPLAY.blit(infoPic,infoRect)
        DISPLAY.blit(infoPic2,infoRect2)
        DISPLAY.blit(infoPic3,infoRect3)
        DISPLAY.blit(infoPic4,infoRect4)
        DISPLAY.blit(infoPic5,infoRect5)

        #Space to go back
        spaceStart = startTitle.render("Press SPACE to go back to title",True,BLACK)
        spaceStartRect = spaceStart.get_rect(center=(WIDTH/2,HEIGHT*.85))
        DISPLAY.blit(spaceStart,spaceStartRect)
        pygame.display.update()

#The start screen
def startScreen():
    start = True
    frames = 0
    colorIndex = 0
    while start:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            #Space to start
            if event.type == KEYDOWN:
                if event.key == K_SPACE:
                    start = False
                if event.key == K_i:
                    infoScreen()
        #Display Title
        DISPLAY.fill(WHITE)
        title = startTitle.render("Triva Game Tester",True,BLACK)
        titleRect = title.get_rect(center=(WIDTH/2,HEIGHT/3))
        titleRect2 = title.get_rect(center=((WIDTH/2)-3,(HEIGHT/3)-2))
        DISPLAY.blit(title,titleRect)
        DISPLAY.blit(startTitle.render("Triva Game Tester",True,GREEN),titleRect2)

        #Changing colors
        spaceStart = startTitle.render("Press SPACE to start",True,colors[colorIndex])
        spaceStartRect = spaceStart.get_rect(center=(WIDTH/2,HEIGHT*.7))
        DISPLAY.blit(spaceStart,spaceStartRect)
        iStart = startTitle.render("Press I for information",True,colors[colorIndex])
        iStartRect = iStart.get_rect(center=(WIDTH/2,HEIGHT*.8))
        DISPLAY.blit(iStart,iStartRect)
        
        if frames%50 == 0:
            colorIndex += 1
            if colorIndex == 7:
                colorIndex = 0
        frames += 1
        
        pygame.display.update()
        pygame.time.wait(20)

#The question screens
def questionScreen(question):
    screen = True
    finished = False
    grabbedOptions = grabRandomAnswers(question[1])
    grabbedOptions.append(question[1])
    selected = 0
    global answeredCorrect
    while screen:
        for event in pygame.event.get():
            if event.type == QUIT:
                screen = False
            if event.type == MOUSEBUTTONDOWN:
                if pygame.mouse.get_pressed()[0]:
                    mouseX = event.pos[0]
                    mouseY = event.pos[1]
                    box = questionMenuClicked(mouseX,mouseY)
                    #Check if clicked is in bounds
                    if box != -1:
                        selected = grabbedOptions[box]
                        finished = True
                        screen = False
                    
        DISPLAY.fill(BLACK)
        
        #Write the Question
        writeQuestion = questionFont.render(question[0],True,GREEN)
        writeQuestionRect = writeQuestion.get_rect(center=(WIDTH/2,HEIGHT*.2))
        DISPLAY.blit(writeQuestion,writeQuestionRect)

        #Show the answer options
        i = 0
        for option in optionCoords:
            pygame.draw.rect(DISPLAY,WHITE,(option[0],option[1],optionWidth,optionHeight),5)
            optionText = cardFont.render(str(grabbedOptions[i]),True,WHITE)
            optionTextRect = optionText.get_rect(center=(option[0]+(optionWidth/2),option[1]+(optionHeight/2)))
            DISPLAY.blit(optionText,optionTextRect)
            i += 1

        #Show correct/incorrect screen
        if finished:
            if selected == question[1]: #Correct
                DISPLAY.fill(GREEN)
                showAnswer = questionFont.render("Correct!",True,WHITE)
                answeredCorrect += 1
                calculateScore()
            else:                       #Incorrect
                DISPLAY.fill(RED)
                showAnswer = questionFont.render("Wrong, the answer was "+str(question[1]),True,WHITE)
                
            #Display correct/incorrect
            showAnswerRect = showAnswer.get_rect(center=(WIDTH/2,HEIGHT/2))
            DISPLAY.blit(showAnswer,showAnswerRect)
            pygame.display.update()
            pygame.time.wait(2000)
        
        pygame.display.update()
        pygame.time.wait(20)

#The main game screen
def mainGame():
    global score
    global answeredCorrect
    global answered
    main = True
    while main:
        for event in pygame.event.get():   
            if event.type == QUIT:
                main = False
            if event.type == MOUSEBUTTONDOWN:
                #Check which box was clicked and pull up the question screen
                if pygame.mouse.get_pressed()[0]:
                    mouseX = event.pos[0]
                    mouseY = event.pos[1]
                    box = mainMenuClicked(mouseX,mouseY)
                    #Check if clicked is in bounds
                    if box != -1:
                        selected = cards[box]
                        #Check if box has been previously selected
                        if selected[3]:
                            questionScreen(selected[2])
                            selected[3] = False
                            answered += 1
                
        DISPLAY.fill(BLACK)
        DISPLAY.blit(titleFont.render("Trivia Time!",True,WHITE), (200, 15)) #Title

        #Print out the cards
        q = 1
        for card in cards:
            if card[3]: #Card available (Bright green)
                pygame.draw.rect(DISPLAY,GREEN,(card[0],card[1],cardWidth,cardHeight))
            else:       #Card answered (Dark green
                pygame.draw.rect(DISPLAY,DARKGREEN,(card[0],card[1],cardWidth,cardHeight))
            #Card outline
            pygame.draw.rect(DISPLAY,WHITE,(card[0],card[1],cardWidth,cardHeight),5)
            #Card text
            cardText = cardFont.render("Question "+str(q),True,BLACK)
            cardTextRect = cardText.get_rect(center=(card[0]+(cardWidth/2),card[1]+(cardHeight/2)))
            DISPLAY.blit(cardText,cardTextRect)
            q += 1

        #Display the score
        showScore = cardFont.render("Score: "+str(score),True,WHITE)
        DISPLAY.blit(showScore,(890,10))

        #Display questions answered correct
        showScore = cardFont.render(str(answeredCorrect)+" correct out of "+str(answered),True,WHITE)
        DISPLAY.blit(showScore,(10,10))

        #If all questions answered, end main screen
        if answered == 16:
            main = False
        pygame.display.update()
        pygame.time.wait(20)

#After game screen
def endScreen():
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

        #Display game finished
        DISPLAY.fill(BLACK)
        finalTitleText = titleFont.render("Game Finished!",True,WHITE)
        finalTitleTextRect = finalTitleText.get_rect(center=(WIDTH/2,100))
        DISPLAY.blit(finalTitleText, finalTitleTextRect)

        #Display questions correct out of 16
        finalText = cardFont.render("You answered "+str(answeredCorrect)+" correct out of 16",True,WHITE)
        finalTextRect = finalText.get_rect(center=(WIDTH/2,HEIGHT/2 + 50))
        DISPLAY.blit(finalText,finalTextRect)
        
        pygame.display.update()
        pygame.time.wait(20)



#Run our functions
startScreen()
mainGame()
endScreen()
