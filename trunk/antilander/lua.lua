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
			elseif(set_com == "bombspeed") then
			Action(11,set_value)
			elseif(set_com == "bombacc") then
			Action(12,set_value)
			elseif(set_com == "bombrad") then
			Action(13,set_value)
			else
			return "nothing"
			end
			
-- EJR added 'spawn' command that takes 1 parameter 'bomb' or 'missile'	
		
		elseif (string.find(cmd,"spawn")~= nil ) then
		    set_com = string.sub(cmd,7,-1)

			if (set_com == "bomb") then
				Action(100,0)
			elseif (set_com == "missile") then
			    Action(101,0)
			elseif (set_com == "lander") then
			    Action(102,0)
			end
		else
			return "unidentified command"	
		end
end



-- AddEntity("George",15.3,10)
-- AddEntity("Eric",15.3,99.1)
-- AddEntity("Vadim",15.3,99.1)
-- AddEntity("Dave",15.3,99.1)
-- AddEntity("Daniel",15.3,99.1)
-- AddEntity("Joseph",15.3,99.1)
-- AddEntity("Adam",53,199.1)
-- AddEntity("Steven",15.3,99.1)
--PrintEntities()

-- Items = {}

-- Items[1] = {	name = "Knife",
				-- weight = 0.75,
				-- value = 7		}

-- Items[2] = {	name = "Pistol",
				-- weight = 3.83,
				-- value = 175		}
				
-- Items.num = 2


-- function AddItem(n, w, v)
	-- Items.num = Items.num + 1
	-- Items[Items.num] = { name = n,
						 -- weight	= w,		
						 -- value = v	}
-- end

-- function PrintItems()
	-- local j
	-- print("\nName","Weight","Value")
	-- for j = 1, Items.num, 1	do
		-- print(Items[j].name, Items[j].weight, Items[j].value)
		
	-- end
-- end				

-- AddItem("Shotgun", 10.9,1234.50)
-- print("")
-- PrintItems()	
			
				
