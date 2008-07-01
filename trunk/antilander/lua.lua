function conInput(cmd)
	local set_com,set_value -- MAKE one time variables local!
  		if (string.find(cmd, "set")~= nil) then
			set_com = string.sub(cmd,5,-1)
			set_value = string.sub(set_com,(string.find(set_com," "))+1,-1)
			set_com = string.sub(set_com,1,string.len(set_com) - string.len(set_value) - 1)
			set_value = tonumber(set_value)
			
			if(set_com == "missiles") then
			Action(1,set_value)
			elseif(set_com == "bombs") then
			Action(2,set_value)
			elseif(set_com == "missilereload") then
			Action(3,set_value)
			elseif(set_com == "landlevel") then
			Action(4,set_value)
			elseif(set_com == "landscreen") then
			Action(5,set_value)
			elseif(set_com == "landpersist") then
			Action(6,set_value)
			elseif(set_com == "landrate") then
			Action(7,set_value)
			elseif(set_com == "missilespeed") then
			Action(8,set_value)
			elseif(set_com == "pad") then
			Action(9,set_value)
			elseif(set_com == "bombreload") then
			Action(10,set_value)
			elseif(set_com == "bombacc") then
			Action(11,set_value)
			elseif(set_com == "bombspeed") then
			Action(12,set_value)
			elseif(set_com == "bombrad") then
			Action(13,set_value)
			elseif(set_com == "exprad") then
			Action(14,set_value)
			elseif(set_com == "exprate") then
			Action(15,set_value)
			else
			return "nothing"
			end
				
			
		elseif (string.find(cmd, "save")~= nil) then
			set_value = string.sub(cmd,6,-1)
			set_value = tonumber(set_value)
			Action(90,set_value)
		elseif (string.find(cmd, "load")~= nil) then
			set_value = string.sub(cmd,6,-1)
			set_value = tonumber(set_value)
			Action(91,set_value)
		elseif (string.find(cmd, "restart")~= nil) then
			set_value = string.sub(cmd,9,-1)
			set_value = tonumber(set_value)
			Action(92,0)
		elseif (string.find(cmd, "quit")~= nil) then
			Action(93,0)
		else
			Action(0,0)
		end
end


