data_origin = [17 17 0 11 16 3 3 12 6 15 13 255 34 19 245 39 24 246 40 28 248 40 32 250 37 33 254 23 30 5 13 26 9 15 23 5 15 21 4 13 19 4 6 15 6 5 12 5 11 12 0 27 16 249 35 21 246 34 25 250 23 24 0 17 22 4 13 20 4 13 18 3 20 18 255];
data = data_origin(1:3:end);
filtered_in_atmega128 = data_origin(2:3:end);
velocity_in_atmega128 = data_origin(3:3:end);

% 칼만 필터 파라미터 설정
Q = 0.1;  % 프로세스 노이즈 공분산
R = 1.0;   % 측정 노이즈 공분산
x = 0;     % 초기 상태 추정
P = 1;     % 초기 오차 공분산

for i = 1:length(data)
    % 예측 단계
    x = x;     % 예측된 상태값
    P = P + Q; % 예측된 오차 공분산

    % 업데이트 단계
    K = P / (P + R); % 칼만 이득
    x = x + K * (filtered_in_atmega128(i) - x); % 측정된 상태값으로 상태값 업데이트
    P = (1 - K) * P; % 오차 공분산 업데이트

    filtered_data(i) = x; % 필터링된 거리 데이터
    estimated_velocity(i) = x / 0.1; % 추정된 속도 데이터 (거리를 시간으로 나누어 계산)
end

% 그래프 그리기
t = 1:length(data); % 시간 인덱스

figure;
subplot(2, 1, 1);
plot(t, data, 'k', t, filtered_in_atmega128, 'r', t, filtered_data, 'b');
title('Distance');
xlabel('Time');
ylabel('Distance');
legend('Original Data', 'Filtered in Atmega128', 'Filtered in Matlab');

subplot(2, 1, 2);
plot(t, velocity_in_atmega128, 'r', t, estimated_velocity, 'b');
title('Velocity');
xlabel('Time');
ylabel('Velocity');
legend('Velocity in Atmega128', 'Velocity in Matlab');