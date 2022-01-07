#!/usr/bin/env python

#import modules
import pygame
import math
import csv
import time

#initialize pygame
pygame.init()

#CLock
clock = pygame.time.Clock()

#RGB Colours
BLUE = (0,0,255)
GREEN = (0,255,0)
RED = (255,0,0)
BLACK = (0,0,0)
WHITE = (255,255,255)

#Set up Window
wn_width = 1000
wn_height = 1000
wn = pygame.display.set_mode((wn_width, wn_height))
pygame.display.set_caption("DFS")

pygame.draw.rect(wn ,WHITE, (11*50,4*50,(16-11)*50,(7-4)*50+30))
pygame.draw.rect(wn ,WHITE, (3*50,14*50,(7-3)*50,(18-14)*50+30))

time.sleep(0.5)

#function to display dot
def display_dot_robot_1(info):

	x = int(info[0])
	x = x*50+20
	y = int(info[1])
	y = y*50+20

	pygame.draw.circle(wn, BLUE, (x, y), 7)

#function to display line
def display_line_robot_1(info, prev_info):

	x = int(info[0])
	x = x*50+20
	y = int(info[1])
	y = y*50+20
	prev_x = int(prev_info[0])
	prev_x = prev_x*50+20
	prev_y = int(prev_info[1])
	prev_y = prev_y*50+20


	pygame.draw.line(wn, BLUE, (x, y), (prev_x, prev_y), 2)

def display_dot_robot_2(info):

	x = int(info[0])
	x = x*50+20
	y = int(info[1])
	y = y*50+20

	pygame.draw.circle(wn, GREEN, (x, y), 7)

#function to display line
def display_line_robot_2(info, prev_info):

	x = int(info[0])
	x = x*50+20
	y = int(info[1])
	y = y*50+20
	prev_x = int(prev_info[0])
	prev_x = prev_x*50+20
	prev_y = int(prev_info[1])
	prev_y = prev_y*50+20

	pygame.draw.line(wn, GREEN, (x, y), (prev_x, prev_y), 2)

def display_dot_robot_3(info):

	x = int(info[0])
	x = x*50+20
	y = int(info[1])
	y = y*50+20

	pygame.draw.circle(wn, RED, (x, y), 7)

#function to display line
def display_line_robot_3(info, prev_info):

	x = int(info[0])
	x = x*50+20
	y = int(info[1])
	y = y*50+20
	prev_x = int(prev_info[0])
	prev_x = prev_x*50+20
	prev_y = int(prev_info[1])
	prev_y = prev_y*50+20

	pygame.draw.line(wn, RED, (x, y), (prev_x, prev_y), 2)

#access csv file
with open('/home/ashd/gazebo_ws/src/stc/src/scripts/3_bots/robot_1_dfs.csv', 'r') as csv_file:
	reader = csv.reader(csv_file, delimiter = ',')
	info = next(reader)
	prev_info=info

	state = True
	while state:
		for event in pygame.event.get():
			if event.type==pygame.QUIT:
				state = False

		try:
			display_dot_robot_1(info)
			display_line_robot_1(info, prev_info)
			prev_info=info
			info = next(reader)

		except:
			break

	
		pygame.display.flip()
		time.sleep(0.05)

csv_file.close()

with open('/home/ashd/gazebo_ws/src/stc/src/scripts/3_bots/robot_2_dfs.csv', 'r') as csv_file:
	reader = csv.reader(csv_file, delimiter = ',')
	info = next(reader)
	prev_info=info

	state = True
	while state:
		for event in pygame.event.get():
			if event.type==pygame.QUIT:
				state = False

		try:
			display_dot_robot_2(info)
			display_line_robot_2(info, prev_info)
			prev_info=info
			info = next(reader)

		except:
			break

	
		pygame.display.flip()
		time.sleep(0.05)

csv_file.close()

with open('/home/ashd/gazebo_ws/src/stc/src/scripts/3_bots/robot_3_dfs.csv', 'r') as csv_file:
	reader = csv.reader(csv_file, delimiter = ',')
	info = next(reader)
	prev_info=info

	state = True
	while state:
		for event in pygame.event.get():
			if event.type==pygame.QUIT:
				state = False

		try:
			display_dot_robot_3(info)
			display_line_robot_3(info, prev_info)
			prev_info=info
			info = next(reader)

		except:
			break

	
		pygame.display.flip()
		time.sleep(0.05)

csv_file.close()

while True:
	pass