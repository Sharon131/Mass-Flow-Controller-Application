# Mass Flow Controller Application

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Features](#features)
* [Status](#status)
* [More Information](#more-information)

## General Info
Final project to classes of Objective Programming on Electronics.   
Application was build in order to remotely communicates with Intrument Brooks' Mass Flow Controller, model 0254.   
Connection is made by RS232 port.

Projekt na zajęcia z Programowania Obiektowego. Zdalne sterowanie przepływomierzem firmy Brooks Instrument.

## Technologies
Language: C++11    
Used API: WinApi

## Features
What you can do through this app:   
* read current settings from Mass Flow Controller
* update settings to Mass Flow Controller (Blending, Batching, Set Point, set Units etc.)

What could be improved:   
* if cable is disconnected from controller after making connection, program will not see that or will crash. In that case it is needed to close the program and then open it once again
* in case of disconnetcting cable from computer after making connection, it is needed to close the program and open it once again

To-do's:    
* add ability to save data to text file
* add ability to read settings from text file

## Status
Project currently is not continued.

## More information

Website with more informaton about the controller: [here](https://www.brooksinstrument.com/en/products/accessories-software/secondary-electronics/0250-power-supply "Brooks Instruments Website")    
Documentation of the controller: [here](../master/PO_dokumenacja_sprzetu.pdf)   
Polish documentation of the program: [here](../master/Dokumentacja_PO.pdf)   
