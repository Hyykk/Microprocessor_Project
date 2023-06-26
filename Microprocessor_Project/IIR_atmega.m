data_origin = [0
0
0
0
0
0
0
0
18
3
0
3
0
2
17
5
18
8
18
10
0
8
0
6
18
9
18
10
18
12
3
10
0
8
17
10
18
12
2
10
0
8
14
9
1
7];
data = data_origin(1:2:end);
filtered_in_atmega128 = data_origin(2:2:end);

% IIR 필터 파라미터 설정
alpha = 0.2; % 알파값

filtered_data_iir = zeros(size(data));

% 초기 필터링 값 설정
filtered_data_iir(1) = alpha * filtered_in_atmega128(1);

% IIR 필터링
for i = 2:length(data)
    filtered_data_iir(i) = alpha * filtered_in_atmega128(i) + (1 - alpha) * filtered_data_iir(i-1);
end

% 그래프 그리기
t = 1:length(data); % 시간 인덱스

figure;
subplot(2,1,1);
    plot(t, data, 'k', t, filtered_in_atmega128, 'r', t, filtered_data_iir, 'b');
    
    title('IIR Filter');
    xlabel('Time');
    ylabel('Temperature(C)');
    legend('Original Data', 'Filtered in Atmega128', 'Filtered in Matlab');
subplot(2,1,2);
    hold on;
    Fs = 1;  % 샘플링 주파수
    N = length(data);  % 데이터 포인트의 개수
    f = (0:N-1)*(Fs/N);  % 주파수 벡터
    
    data_fft = fft(data);  % FFT 적용
    fa_fft = fft(filtered_in_atmega128);  % FFT 적용
    fm_fft = fft(filtered_data_iir);  % FFT 적용
    
    stem(f, abs(data_fft), 'k', 'LineWidth', 2.0);  % 주파수 영역의 그래프 (파란색 선)
    stem(f, abs(fa_fft), 'r', 'LineWidth', 1.5);  % 주파수 영역의 그래프 (파란색 선)
    stem(f, abs(fm_fft), 'b', 'LineWidth', 1.0);  % 주파수 영역의 그래프 (파란색 선)

    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    legend('Original Data', 'Filtered in Atmega128','Filtered in Matlab');
    title('FFT');
    grid on;