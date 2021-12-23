from cs50 import get_string

#  this program detect difficulty of sentence
#  compute number of letters , words  and sentences .
#  then according to formula find grade of difficulty
#  finally show correct grade

# Get input sample
sample = get_string("Please type your Text : ")


# TODO: compute Grade
letter = 0
word = 0
sentence = 0
letter2 = 0
sentence2 = 0
grade = 0

for i in range(len(sample)):
    if (sample[i] == "." or sample[i] == "!" or sample[i] == "?"):
        sentence = sentence+1

    elif (sample[i] == " "):
        word = word+1

    elif (sample[i] == "-" or sample[i] == "," or sample[i] == 39 or sample[i] == 34):
        #  - ,  , , ' , " , `
        grade = grade+1
    else:
        letter = letter+1

grade = 0
letter2 = (letter * 100) / word
sentence2 = (sentence * 100) / word
grade = round(0.0588 * letter2 - 0.296 * sentence2 - 15.8)

if (grade < 1):
    print("Before Grade 1")

elif (grade > 16):
    print("Grade 16+")
else:
    print("Grade", grade)