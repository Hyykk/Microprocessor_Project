data_origin = [00472 00472 00466 00471 00255 00449 00074 00409 00000 00362 00000 00315 00000 00268 00000 00221 00081 00182 00299 00164 00377 00155 00092 00117 00189 00111 00771 00180 00737 00254 00318 00286 00000 00286 00000 00286 00455 00323 00649 00358 00252 00346 00094 00346 00669 00394 00824 00399 01023 00428 00847 00481 00148 00496 00000 00496 00268 00477 00185 00431 00422 00447 00519 00490 00922 00515 00270 00460 00971 00455 00941 00464 00951 00544 00964 00641];
data = data_origin(1:2:end);
filtered_in_atmega128 = data_origin(2:2:end);

% FIR 필터 파라미터 설정
order = 10;     % 필터 차수
coefficients = 0.1 * ones(1, order);  % 계수

filtered_data_fir = zeros(size(data));

% FIR 필터링
for i = order:length(data)
    filtered_data_fir(i) = sum(coefficients .* filtered_in_atmega128(i:-1:i-order+1));
end

% 그래프 그리기
t = 1:length(data); % 시간 인덱스
figure;
subplot(2,1,1);
    plot(t, data, 'k', t, filtered_in_atmega128, 'b', t, filtered_data_fir, 'r');
    title('FIR Filter');
    xlabel('Time');
    ylabel('ADC');
    legend('Original Data' ,'Filtered in Atmega128)', 'Filtered in Matlab');

subplot(2,1,2);
    hold on;
    Fs = 1;  % 샘플링 주파수
    N = length(data);  % 데이터 포인트의 개수
    f = (0:N-1)*(Fs/N);  % 주파수 벡터
    
    data_fft = fft(data);  % FFT 적용
    fa_fft = fft(filtered_in_atmega128);  % FFT 적용
    fm_fft = fft(filtered_data_fir);  % FFT 적용
    
    stem(f, abs(data_fft), 'k', 'LineWidth', 2.0);  % 주파수 영역의 그래프 (파란색 선)
    stem(f, abs(fa_fft), 'r', 'LineWidth', 1.5);  % 주파수 영역의 그래프 (파란색 선)
    stem(f, abs(fm_fft), 'b', 'LineWidth', 1.0);  % 주파수 영역의 그래프 (파란색 선)

    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    legend('Original Data', 'Filtered in Atmega128','Filtered in Matlab');
    title('FFT');
    grid on;