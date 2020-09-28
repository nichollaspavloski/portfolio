<template>
    <div class="container">
        <h1>Registro de ponto de funcionários</h1>
        <hr />
        <div class="form-todo form-group">
            <div class="col-xs-2">
                <label for="ex1">
                    <input placeholder="Nome" class="form-control" type="text"
                    v-model="nameEmploye" /> <br />
                    <input placeholder="RG" class="form-control" type="text"
                    v-model="rgEmploye" /> <br />
                    <input placeholder="Cidade" class="form-control" type="text"
                    v-model="cityEmploye" />
                </label>
            </div>

            <button v-on:click="register" type="submit" class="btn btn-primary">
                Registrar
            </button>
        </div>
        <div class="list-group">
            <div v-for="(emp, index) in idRegister" :key="emp.id" class="list-group-item">
                <div class="col-xs-2">
                    <label for="ex1">Funcionário: {{  emp.nameEmploye  }}   
                        <input placeholder="Atualizar nome" class="form-control"
                        type="text" v-model="emp.nameEmploye" />
                        RG: {{  emp.rgEmploye  }} <br />
                        <input placeholder="Atualizar RG" class="form-control"
                        type="text" v-model="emp.rgEmploye" />
                        Cidade: {{  emp.cityEmploye  }}
                        <input placeholder="Atualizar cidade" class="form-control"
                        type="text" v-model="emp.cityEmploye" />    
                    </label>
                </div>

                <div>
                    <input type="time" v-bind:id="emp.vControl[0]" />
                    <input type="time" v-bind:id="emp.vControl[1]" />
                    <button v-on:click.prevent="scheduleRegister(index)" class="btn">
                        Registrar horário
                    </button>
                </div>

                <li v-for="sch in emp.schedules" :key="sch.id" class="list-group-item">
                    <input type="time" v-model="sch.inTime" />
                    <input type="time" v-model="sch.outTime" />
                    <button v-on:click.prevent="deleteSchedule(index, sch)" class="btn">
                        Excluir horário
                    </button>   
                </li>

                <h5> Carga horária = {{ emp.workload }} </h5>

                <button v-on:click.prevent="deleteEmploye(index)" class="btn">
                    Excluir funcionário | 
                </button>
                <button v-on:click.prevent="calculateWorkload(index)" class="btn">
                    Calcular carga horária
                </button>
            </div>
        </div>
        <hr />
    </div>
</template>

<script>
const idRegister = [];

export default {
    data(){
        return {
            idRegister: idRegister
        }
    },

    methods: {

        register(){
            if(this.nameEmploye.trim() === '' || this.rgEmploye.trim() === '' || this.cityEmploye.trim() === ''){
                return;
            }

            idRegister.push({
                nameEmploye: this.nameEmploye,
                rgEmploye: this.rgEmploye,
                cityEmploye: this.cityEmploye,
                vControl: [`inTime${idRegister.length + 1}`, `outTime${idRegister.length + 1}`],
                schedules: [],
                workload: ""
            });

            this.nameEmploye = '';
            this.rgEmploye = '';
            this.cityEmploye = '';
        },

        scheduleRegister(index) {
            const idEmploye = index + 1;
            const inTime = document.getElementById('inTime' + idEmploye);
            const outTime = document.getElementById('outTime' + idEmploye);

            idRegister[index].schedules.push({
                inTime: inTime.value,
                outTime: outTime.value
            });

            inTime.value = "";
            outTime.value = "";
        },

        deleteSchedule(index, sch) {
            idRegister[index].schedules.splice(sch, 1);
        },

        deleteEmploye(index){
            idRegister.splice(index, 1);
        },

        calculateWorkload(index){
            let hours = 0;

            idRegister[index].schedules.forEach(j => {
                const inT = j.inTime.split(':');
                const outT = j.outTime.split(':');

                let totalHours = parseInt(outT[0], 10) - parseInt(inT[0], 10);
                let totalMin = parseInt(outT[1], 10) - parseInt(inT[1], 10);

                if(totalMin < 0) {
                    totalMin += 60;
                    totalHours -= 1;
                }

                hours += totalHours + totalMin/60;
            });

            const h = hours - hours%1;
            const m = 60*(hours%1);
            const t = h + "h" + ("00" + Math.round(m)).slice(-2);

            idRegister[index].workload = t;
        }
    }
}
</script>