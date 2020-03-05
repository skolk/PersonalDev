#!/usr/bin/env python

__author__ =  "Blaze Sanders"
__email__ =   "blaze.d.a.sanders@gmail.com"
__company__ = "Ace Toy Company"
__status__ =  "Development"
__date__ =    "Late Updated: 2019-05-31"
__doc__ =     "Main control code for 8 Ball project"

# Pull and process JSON formatted data from a URL database
import requests

# Modular plug and play control of motors, servos, and relays
import Acutator

###
# 
#
# Return TRUE if fobID is in list of valid IDs, FASLE otherwise
###
def isValid(fobID):

	validIDs = [1234, 9876, 5555, 0000]
	idFound = False
	for i in validIDs:
		if(fobID == validIDs[i]):
			idFound = True

	return  idFound

if __name__ ==  "__main__":
	r = requests.get('https://nomcon.foballthethings.org/api')

	#TODO curl -X GET --header 'Accept: application/coreapi+json' --header 'Authorization: 2e77c0656e0549e4cefadfac979ccc622b98b07f' 'https://nomcon.foballthethings.org/api/'

	while True:
		try:
			r.json()
		except (ValueError, RuntimeError, TypeError, NameError):
			#Value Error thrown when no JSON object could be decoded
			print("BAD STUFF HAPPENED")

		fobID = r.ID

		if(isValid(fobID)):
			#TODO HDMI  STUFF


