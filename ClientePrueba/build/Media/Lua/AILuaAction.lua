PI = 3.1416
event = {
    ["NO_EVENT"] = 0,
    ["PLAYER_SET_WEAPON_KNIFE"] = 1,
    ["PLAYER_SET_WEAPON_GUN"] = 2,
    ["PLAYER_SET_WEAPON_SECONDARY"] = 3,
    ["PLAYER_START_MOVING_FORWARD"] = 4,
    ["PLAYER_START_MOVING_BACKWARD"] = 5,
    ["PLAYER_STOP_MOVING"] = 6,
    ["PLAYER_START_ROTATING_RIGHT"] = 7,
    ["PLAYER_START_ROTATING_LEFT"] = 8,
    ["PLAYER_STOP_ROTATING"] = 9,
    ["PLAYER_SHOOT"] = 10,
    ["PLAYER_STOP_SHOOTING"] = 11,
    ["PLAYER_START_OPENING_DOOR"] = 12,
    ["PLAYER_STOP_OPENING_DOOR"] = 13
}

function getIdleEvent(rotating, moving)
    if(moving == true) then
        moving = false
        return event["PLAYER_STOP_MOVING"], rotating, moving
    else
        rotating = true
        return event["PLAYER_START_ROTATING_RIGHT"], rotating, moving
    end
end

function getEvent(playerAng, enemyAng, dist, shooting, rotating, moving)
    if(dist < 100) then
        return event["PLAYER_SHOOT"], shooting, rotating, moving
    end

    local relativeAng;
    local auxAngle;
    if(enemyAng-playerAng >5.5) then
        relativeAng = auxAngle-playerAng - 2*PI
    elseif(enemyAng-playerAng<-5.5) then
        relativeAng = enemyAng-auxAngle+ 2*PI
    else
        relativeAng = enemyAng-playerAng
    end

    if(relativeAng >= 15*PI/180) then
        if(moving == true) then
            moving = false
            return event["PLAYER_STOP_MOVING"], shooting, rotating, moving
        else
            rotating = true
            return event["PLAYER_START_ROTATING_RIGHT"], shooting, rotating, moving
        end
    elseif(relativeAng <= -15*PI/180) then
        if(moving == true) then
            moving = false
            return event["PLAYER_STOP_MOVING"], shooting, rotating, moving
        else
            rotating = true
            return event["PLAYER_START_ROTATING_LEFT"], shooting, rotating, moving
        end
    else
        if(rotating == true) then
            rotating = false
            return event["PLAYER_STOP_ROTATING"], shooting, rotating, moving
        else
            moving = true
            return event["PLAYER_START_MOVING_FORWARD"], shooting, rotating, moving
        end
    end
end

function objIsVisible(playerX, playerY, enemyX, enemyY, ang)
    local gVis = 35.0/180.0
    local visible = PI * gVis
    local dx = enemyX - playerX
    local dy = enemyY - playerY

    local angleObj = math.atan(dy, dx)
    local difAng = ang - angleObj

    if (difAng < -PI) then
        difAng = difAng + 2*PI
    end
    if (difAng > PI) then
        difAng = difAng - 2*PI
    end
    local res = (difAng < visible)
    res = res and (difAng > -visible)

    return res
end

