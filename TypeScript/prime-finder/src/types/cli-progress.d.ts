declare module 'cli-progress' {
    export class SingleBar {
        constructor(options?: any, preset?: any);
        start(total: number, startValue: number): void;
        update(currentValue: number): void;
        stop(): void;
    }

    export const Presets: {
        shades_classic: any;
        shades_grey: any;
    };
}