# Project Name: Finding Prime Numbers Using TypeScript

A prime number is a number that can only be divided by itself and 1 without remainders. 

## How to setup step by step?
1. Create a package.json file
```bash
yarn init -y
```

2. Install TypeScript and Dependencies
```bash
yarn add typescript --dev
yarn add @types/node --dev
yarn add @types/cli-progress --dev
yarn add cli-progress
```

3. Create a tsconfig.json file to configure TypeScript
```bash
yarn tsc --init
```

4. Modify the tsconfig.json
```json
{
  "compilerOptions": {
    "target": "ES6",             
    "module": "commonjs",       
    "strict": true,             
    "esModuleInterop": true,    
    "skipLibCheck": true,       
    "forceConsistentCasingInFileNames": true,
    "outDir": "./dist"         
  },
  "include": ["src/**/*.ts"],     
  "exclude": ["node_modules"]   
}
```

5. Add build and run scripts In your package.json
```json
"scripts": {
  "build": "tsc",
  "start": "node dist/PrimeNumbers.js"
}
```

6. Compile TypeScript
```bash
yarn build
```

7. Run the compiled JavaScript
```bash
yarn start
```

# Project Folder Structure

my-typescript-project/
├── dist/
│   └── PrimeNumbers.js  
├── node_modules	
├── src/
│   └── PrimeNumbers.ts                          
├── package.json               
├── tsconfig.json             
├── yarn.lock
