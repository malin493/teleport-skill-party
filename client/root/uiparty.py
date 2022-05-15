#find  __ShowStateButton

#add
		## Warp
		if self.stateButtonDict.has_key(self.MEMBER_BUTTON_WARP):
			button = self.stateButtonDict[self.MEMBER_BUTTON_WARP]
			button.SetPosition(xPos, y)
			button.Show()
			xPos += 23