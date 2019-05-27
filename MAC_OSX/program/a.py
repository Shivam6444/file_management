import os
import tkinter as tk
from tkinter import filedialog
from tkinter import *

#import tkFileDialog as filedialog

root = tk.Tk()
root.title("Application Name")
root.geometry("640x640+0+0")
root.update()

root.filename = filedialog.askdirectory()

command = "ls \""+root.filename+"\" | sort >> temp.txt"
print(command)
os.system(command)

label = Label(root, text="Enter The Special Char: ",font=("arial",20,"bold"), fg="black").place(x=10,y=200)

name = StringVar()
entry_box = Entry(root,textvariable=name,width=25,bg="lightgreen").place(x=280,y=210) 

def do_it():
	symbol = str(name.get())[0]
	print("symbol"+symbol)
	process(symbol)


work = Button(root, text="Work",width=30,height=5,bg="lightblue",command=do_it).place(x=250,y=300)
filename1 = "temp.txt"
def process(symbol):
	os.system("mkdir ./output")
	file = open(filename1, "r")
	for line in file:
		line = line.replace('\n', '')
		splittedString = line.split(symbol,1)
		if not os.path.exists("./output/"+splittedString[0]):
			os.makedirs("./output/"+splittedString[0])
		myCommand = "cp \""+root.filename+"/"+line+"\""+" \"./output/"
		myCommand = myCommand+splittedString[0]+"\""
		myCommand = myCommand.replace('\n', '')
		print(myCommand)
		os.system(myCommand)

		if not os.path.exists("./output/"+splittedString[0]+"/Picks"):
			os.makedirs("./output/"+splittedString[0]+"/Picks")
		if not os.path.exists("./output/"+splittedString[0]+"/Culls"):
			os.makedirs("./output/"+splittedString[0]+"/Culls")
	os.system("rm temp.txt");		
	exit()


root.mainloop()
input("Press any button to exit")
