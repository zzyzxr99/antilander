function conInput(cmd)		
		if (string.find(cmd, "set")~= nil) then
			set_com = string.sub(cmd,5,-1)
			set_value = string.sub(set_com,(string.find(set_com," "))+1,-1)
			set_com = string.sub(set_com,1,string.len(set_com) - string.len(set_value) - 1)
			set_value = tonumber(set_value)
			
			if(set_com == "missiles") then
			Action(1,set_value)
			elseif(set_com == "bombs") then
			Action(2,set_value)
			-- elseif(set_com == "reload") then
			-- action(3,set_value)			
			-- elseif(set_com == "missile speed") then
			-- action(4,set_value)
			else
			return "incorrect use of 'set'"
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
			
				