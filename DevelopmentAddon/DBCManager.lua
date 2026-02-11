-- DBC Management Tab
function SylianDevAddon:LoadDBCTab(parent)
    local yOffset = -10
    
    -- Title
    local title = parent:CreateFontString(nil, "OVERLAY", "GameFontNormal")
    title:SetPoint("TOP", 0, yOffset)
    title:SetText("|cff00ccffDBC Hot Reload Tool|r")
    yOffset = yOffset - 30
	
	-- DBC Name input box
	local editBox = CreateFrame("EditBox", "DBCReloadEditBox", parent, "InputBoxTemplate")
	editBox:SetSize(200, 24)
	editBox:SetPoint("TOP", 0, yOffset)
	editBox:SetAutoFocus(false)
	editBox:SetScript("OnEnterPressed", function(self)
		self:ClearFocus()
		reloadDBC(editBox:GetText());
	end)
	yOffset = yOffset - 30
	
    -- DBC Reloader
    local dbcReloadBtn = CreateFrame("Button", nil, parent, "UIPanelButtonTemplate")
    dbcReloadBtn:SetSize(200, 30)
    dbcReloadBtn:SetPoint("TOP", 0, yOffset)
    dbcReloadBtn:SetText("Reload DBC")
    dbcReloadBtn:SetScript("OnClick", function()
	
		reloadDBC(editBox:GetText())
    end)
    yOffset = yOffset - 40
    
end

function reloadDBC(inputText)
    local name = inputText;
    
    -- Check if name is empty or just whitespace
    if name and name:match("^%s*$") then
        name = nil
    end
    
    if name then
        -- Call the global HotReloadDBC function with the name
        if HotReloadDBC then
            HotReloadDBC(name)
            statusText:SetText("Reloading DBC: " .. name)
            statusText:SetTextColor(0, 1, 0)
        else
            statusText:SetText("Error: HotReloadDBC not available")
            statusText:SetTextColor(1, 0, 0)
            print("HotReloadDBC function not available in this client build.")
        end
    else
        -- No name: call without argument to reload all
        if HotReloadDBC then
            HotReloadDBC()
            statusText:SetText("Reloading all DBCs...")
            statusText:SetTextColor(0, 1, 0)
        else
            statusText:SetText("Error: HotReloadDBC not available")
            statusText:SetTextColor(1, 0, 0)
            print("HotReloadDBC function not available in this client build.")
        end
    end
end