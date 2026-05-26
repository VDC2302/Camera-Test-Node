% --- CUSTOMER MATLAB PROTOTYPE ---
% Calculates mechanical sensitivity (displacement per mA)
function [isPass, sensitivity_um_mA] = verifyActuator(stroke_um, current_mA)
    
    % Prevent division by zero error
    if current_mA == 0
        isPass = false;
        sensitivity_um_mA = 0;
        return;
    end

    % Calculate sensitivity
    sensitivity_um_mA = stroke_um / current_mA;

    % Spec Limits provided by Mechanical Team
    LSL = 0.32; % Lower Spec Limit
    USL = 0.38; % Upper Spec Limit

    % Evaluate
    if sensitivity_um_mA >= LSL && sensitivity_um_mA <= USL
        isPass = true;
    else
        isPass = false;
    end
end