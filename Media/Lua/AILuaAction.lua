PI = 3.1416
event = {
    [NO_EVENT] = 0,
    [PLAYER_SET_WEAPON_KNIFE] = 1,
    [PLAYER_SET_WEAPON_GUN] = 2,
    [PLAYER_SET_WEAPON_SECONDARY] = 3,
    [PLAYER_START_MOVING_FORWARD] = 4,
    [PLAYER_START_MOVING_BACKWARD] = 5,
    [PLAYER_STOP_MOVING] = 6,
    [PLAYER_START_ROTATING_RIGHT] = 7,
    [PLAYER_START_ROTATING_LEFT] = 8,
    [PLAYER_STOP_ROTATING] = 9,
    [PLAYER_SHOOT] = 10,
    [PLAYER_STOP_SHOOTING] = 11,
    [PLAYER_START_OPENING_DOOR] = 12,
    [PLAYER_STOP_OPENING_DOOR] = 13
}

moving = false
rotating = false
attacking = false

function doSomething(event, relativeAng, dist)
    -- if(dist < 100) then
        -- event = PLAYER_SHOOT;
    if(relativeAng >= PI/180) then
        if(rotating == true) then
            return event[PLAYER_START_MOVING_FORWARD];
            moving = true;
        else
            return event[PLAYER_START_ROTATING_RIGHT];
           rotating = true;
        end
    elseif(relativeAng <= -15*PI/180) then
        if(rotating) then
            return event[PLAYER_START_MOVING_FORWARD];
            moving = true;
        else
            return event[PLAYER_START_ROTATING_LEFT];
            rotating = true;
        end
    elseif(relativeAng < 15*PI/180 and relativeAng > -15*PI/180) then
        return event[PLAYER_STOP_ROTATING];
        rotating = false;
    end
end

function objIsVisible(playerX, playerY, enemyX, enemyY, ang)
    local gVis = 35.0/180.0
    local visible = PI * gVis

    local dx = enemyX - playerX
    local dy = enemyY - playerY

    -- local angleObj = atan2(dy, dx)
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

